/**
     fifo_driver.c - thread safe

     Date : Mon Sep 28 12:08:40 PDT 2026
     Folsom, CA 95630
**/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/spinlock.h>
#include <linux/wait.h>

#define DEVICE_NAME "atclib-fifo"
#define FIFO_SIZE   256

struct fifo_device {
    char buffer[FIFO_SIZE];

    size_t head;       /* next byte to read */
    size_t tail;       /* next byte to write */
    size_t count;      /* bytes currently stored */

    spinlock_t lock;

    wait_queue_head_t read_queue;
    wait_queue_head_t write_queue;

    struct cdev cdev;
};

static struct fifo_device fifo_dev;
static dev_t dev_num;
static struct class *fifo_class;

/*
 * FIFO helpers
 *
 * Caller MUST hold fifo_dev.lock.
 */

static size_t fifo_space(struct fifo_device *dev)
{
    return FIFO_SIZE - dev->count;
}

static size_t fifo_count(struct fifo_device *dev)
{
    return dev->count;
}

/*
 * read()
 *
 * Userspace:
 *
 *     read(fd, buffer, size);
 *
 * Blocks if FIFO is empty.
 */
static ssize_t fifo_read(struct file *file,
                         char __user *user_buf,
                         size_t len,
                         loff_t *offset)
{
    struct fifo_device *dev = &fifo_dev;
    unsigned long flags;

    char temp[FIFO_SIZE];
    size_t bytes;
    size_t i;

    if (len == 0)
        return 0;

    /*
     * Sleep until FIFO contains data.
     *
     * DO NOT hold spinlock while sleeping.
     */
    if (wait_event_interruptible(dev->read_queue,
                                 READ_ONCE(dev->count) > 0))
        return -ERESTARTSYS;

    /*
     * Protect FIFO state.
     */
    spin_lock_irqsave(&dev->lock, flags);
    bytes = min(len, dev->count);
    /*
     * Copy FIFO -> temporary kernel buffer.
     */
    for (i = 0; i < bytes; i++) {
        temp[i] = dev->buffer[dev->head];
        dev->head =
            (dev->head + 1) % FIFO_SIZE;
    }

    dev->count -= bytes;
    spin_unlock_irqrestore(&dev->lock, flags);

    /*
     * IMPORTANT:
     *
     * copy_to_user() may sleep.
     *
     * Therefore we must NOT hold the spinlock.
     */
    if (copy_to_user(user_buf, temp, bytes))
        return -EFAULT;
    /*
     * We freed FIFO space.
     *
     * Wake writers waiting for space.
     */
    wake_up_interruptible(&dev->write_queue);
    return bytes;
}

/*
 * write()
 *
 * Userspace:
 *
 *     write(fd, buffer, size);
 *
 * Blocks if FIFO is full.
 */
static ssize_t fifo_write(struct file *file,
                          const char __user *user_buf,
                          size_t len,
                          loff_t *offset)
{
    struct fifo_device *dev = &fifo_dev;
    unsigned long flags;

    char temp[FIFO_SIZE];

    size_t bytes;
    size_t space;
    size_t i;

    if (len == 0)
        return 0;

    /*
     * We cannot copy more than our temporary
     * kernel buffer.
     */
    bytes = min(len, (size_t)FIFO_SIZE);

    /*
     * copy_from_user() can sleep.
     *
     * Do this BEFORE taking spinlock.
     */
    if (copy_from_user(temp, user_buf, bytes))
        return -EFAULT;

    /*
     * Wait until FIFO has free space.
     */
    if (wait_event_interruptible(dev->write_queue,
                                 READ_ONCE(dev->count) < FIFO_SIZE))
        return -ERESTARTSYS;

    spin_lock_irqsave(&dev->lock, flags);
    space = fifo_space(dev);
    bytes = min(bytes, space);


    /*
     * Copy temporary buffer -> FIFO
     */
    for (i = 0; i < bytes; i++) {
        dev->buffer[dev->tail] = temp[i];
        dev->tail =
            (dev->tail + 1) % FIFO_SIZE;
    }

    dev->count += bytes;
    spin_unlock_irqrestore(&dev->lock, flags);

    /*
     * FIFO now contains data.
     *
     * Wake readers.
     */
    wake_up_interruptible(&dev->read_queue);
    return bytes;
}

/*
 * open()
 */
static int fifo_open(struct inode *inode,
                     struct file *file)
{
    pr_info("atclib-fifo: device opened\n");
    return 0;
}

/*
 * release()
 */
static int fifo_release(struct inode *inode,
                        struct file *file)
{
    pr_info("atclib-fifo: device closed\n");

    return 0;
}

static const struct file_operations fifo_fops = {
    .owner   = THIS_MODULE,
    .open    = fifo_open,
    .release = fifo_release,
    .read    = fifo_read,
    .write   = fifo_write,
};

/*
 * Module initialization
 */
static int __init fifo_init(void)
{
    int ret;
    /*
     * Initialize FIFO
     */
    fifo_dev.head  = 0;
    fifo_dev.tail  = 0;
    fifo_dev.count = 0;
    /*
     * Initialize synchronization
     */
    spin_lock_init(&fifo_dev.lock);
    init_waitqueue_head(&fifo_dev.read_queue);
    init_waitqueue_head(&fifo_dev.write_queue);

    /*
     * Allocate device number
     */
    ret = alloc_chrdev_region(&dev_num,
                              0,
                              1,
                              DEVICE_NAME);

    if (ret < 0) {
        pr_err("atclib-fifo: alloc_chrdev_region failed\n");
        return ret;
    }

    /*
     * Initialize character device
     */
    cdev_init(&fifo_dev.cdev,
              &fifo_fops);

    fifo_dev.cdev.owner = THIS_MODULE;
    ret = cdev_add(&fifo_dev.cdev,
                   dev_num,
                   1);

    if (ret < 0) {
        unregister_chrdev_region(dev_num, 1);
        return ret;
    }


    /*
     * Create class
     */
    fifo_class = class_create(DEVICE_NAME);

    if (IS_ERR(fifo_class)) {

        cdev_del(&fifo_dev.cdev);
       unregister_chrdev_region(dev_num, 1);
        return PTR_ERR(fifo_class);
    }

    /*
     * Create:
     *
     * /dev/atclib-fifo
     */
    device_create(fifo_class,
                  NULL,
                  dev_num,
                  NULL,
                  DEVICE_NAME);

    pr_info("ç: loaded\n");

    pr_info("atclib-fifo: major=%d minor=%d\n",
            MAJOR(dev_num),
            MINOR(dev_num));
    return 0;
}

/*
 * Module cleanup
 */
static void __exit fifo_exit(void)
{
    device_destroy(fifo_class,
                   dev_num);

    class_destroy(fifo_class);
    cdev_del(&fifo_dev.cdev);
    unregister_chrdev_region(dev_num,
                             1);
    pr_info("atclib-fifo: unloaded\n");
}


module_init(fifo_init);
module_exit(fifo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Atul Raut");
MODULE_DESCRIPTION(
    "Thread-safe circular FIFO character driver");
