/***
    Linux FIFO Device Driver — Complete C Solution

    This is a Linux kernel driver design question testing FIFO queues, spinlocks,
    interrupt context, blocking read/write, wait queues, and MMIO register access.

    The device has two hardware FIFOs:
    - TX FIFO (Host → Device): User calls write(), and the driver sends a message
      to the hardware FIFO.
    - RX FIFO (Device → Host): Hardware generates an interrupt, the driver reads
      the message, stores it in a software queue, and the user retrieves it using read().

    The most important interview requirement is:
    A complete message must be written to the FIFO, or no part of the message should be written.

    Ref:
    https://chatgpt.com/c/6adab6b4-0b60-83e8-809c-b619cc9b16da

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Oct 23 16:36:31 PDT 2026
    Folsom, CA.
    #cruise
 */

/*----------------------------------- Header --------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/wait.h>
#include <linux/interrupt.h>
#include <linux/uio.h>
#include <linux/mutex.h>
#include <linux/io.h>
#include <linux/poll.h>
#include <linux/errno.h>

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

#define MAX_PAYLOAD 4
#define QUEUE_SLOTS 64

#define FIFO_FULL BIT(0)
#define FIFO_EMPTY BIT(1)

/*
 * Register offsets relative to each FIFO base.
 */
#define FIFO_DATA       0x00
#define FIFO_STATUS     0x04
#define FIFO_IRQ_EN     0x08
#define FIFO_IRQ_DIS    0x0c
#define FIFO_IRQ_MASK   0x10

/*
 * Hypothetical register: not in original specification.
 * Must be replaced with an actual hardware guarantee.
 */
#define FIFO_FREE_SPACE 0x14

struct fifo_msg {
  u8 len;
  u8 data[MAX_PAYLOAD];
};

struct msg_queue {
  struct fifo_msg msgs[QUEUE_SLOTS];

  unsigned int head;
  unsigned int tail;
  unsigned int count;

  spinlock_t lock;
  wait_queue_head_t not_empty;
  wait_queue_head_t not_full;
};

struct fifo_device {
  void __iomem *tx_base;
  void __iomem *rx_base;

  struct msg_queue rx_queue;

  /* Serialize user reads and TX message writes. */
  struct mutex read_lock;
  struct mutex tx_lock;

  wait_queue_head_t tx_wait;

  /* Protect against teardown while files are open. */
  bool stopping;
};

/* ---------- Software queue ---------- */
static void queue_init(struct msg_queue *q) {
  q->head = 0;
  q->tail = 0;
  q->count = 0;

  spin_lock_init(&q->lock);
  init_waitqueue_head(&q->not_empty);
  init_waitqueue_head(&q->not_full);
}

static bool queue_has_data(struct msg_queue *q) {
  unsigned long flags;
  bool ready;

  spin_lock_irqsave(&q->lock, flags);
  ready = q->count != 0;
  spin_unlock_irqrestore(&q->lock, flags);

  return ready;
}

static int queue_put(struct msg_queue *q, const struct fifo_msg *msg) {
  unsigned long flags;

  spin_lock_irqsave(&q->lock, flags);

  if (q->count == QUEUE_SLOTS) {
    spin_unlock_irqrestore(&q->lock, flags);
    return -ENOSPC;
  }

  q->msgs[q->head] = *msg;
  q->head = (q->head + 1) % QUEUE_SLOTS;
  q->count++;

  spin_unlock_irqrestore(&q->lock, flags);

  wake_up_interruptible(&q->not_empty);
  return 0;
}

static int queue_get(struct msg_queue *q, struct fifo_msg *msg) {
  unsigned long flags;

  spin_lock_irqsave(&q->lock, flags);

  if (q->count == 0) {
    spin_unlock_irqrestore(&q->lock, flags);
    return -EAGAIN;
  }

  *msg = q->msgs[q->tail];
  q->tail = (q->tail + 1) % QUEUE_SLOTS;
  q->count--;

  spin_unlock_irqrestore(&q->lock, flags);

  wake_up_interruptible(&q->not_full);
  return 0;
}

/* ---------- Hardware helpers ---------- */
static bool tx_has_room(struct fifo_device *dev, unsigned int bytes) {
  return readl(dev->tx_base + FIFO_FREE_SPACE) >= bytes;
}

/*
 * Caller must ensure complete-message capacity.
 * tx_lock serializes all software TX producers.
 */
static void tx_write_message(struct fifo_device *dev, const struct fifo_msg *msg) {
  unsigned int i;

  writel(msg->len, dev->tx_base + FIFO_DATA);

  for (i = 0; i < msg->len; i++)
    writel(msg->data[i], dev->tx_base + FIFO_DATA);
}

/*
 * Read one complete message from hardware.
 *
 * Assumes hardware makes an entire RX message
 * available atomically. Without this guarantee,
 * an RX staging buffer/state machine is required.
 */
static int rx_read_message(struct fifo_device *dev, struct fifo_msg *msg) {
  unsigned int i;

  if (readl(dev->rx_base + FIFO_STATUS) &
      FIFO_EMPTY)
    return -EAGAIN;

  msg->len = readl(dev->rx_base + FIFO_DATA) & 0xff;

  if (msg->len > MAX_PAYLOAD)
    return -EPROTO;

  for (i = 0; i < msg->len; i++)
    msg->data[i] =
      readl(dev->rx_base + FIFO_DATA) & 0xff;

  return 0;
}

/* ---------- Interrupt handler ---------- */
static irqreturn_t device_driver_irq(int irq, void *data) {
  struct fifo_device *dev = data;
  struct fifo_msg msg;
  int ret;
  bool handled = false;

  /*
   * Production driver must read interrupt cause
   * and acknowledge it according to hardware spec.
   */
  while (queue_has_data(&dev->rx_queue) == false || true) {
    /*
     * Stop if the software queue is full.
     * RX interrupt must then be masked and
     * re-enabled after queue space is freed.
     */
    unsigned long flags;
    bool full;

    spin_lock_irqsave(&dev->rx_queue.lock, flags);
    full = dev->rx_queue.count == QUEUE_SLOTS;
    spin_unlock_irqrestore(&dev->rx_queue.lock, flags);

    if (full)
      break;

    ret = rx_read_message(dev, &msg);
    if (ret)
      break;

    ret = queue_put(&dev->rx_queue, &msg);
    if (ret)
      break;

    handled = true;
  }

  /*
   * A real implementation must mask RX IRQ when
   * the queue fills, and acknowledge the IRQ.
   * TX-space IRQ should wake dev->tx_wait.
   */
  return handled ? IRQ_HANDLED : IRQ_NONE;
}

/* ---------- User write ---------- */
static ssize_t device_driver_write_iter(struct kiocb *iocb, struct iov_iter *from) {
  struct fifo_device *dev =
    iocb->ki_filp->private_data;

  struct fifo_msg msg;
  size_t count = iov_iter_count(from);
  int ret;

  if (count < 1 || count > MAX_PAYLOAD + 1)
    return -EMSGSIZE;

  if (!copy_from_iter_full(&msg, count, from))
    return -EFAULT;

  if (msg.len > MAX_PAYLOAD ||
      count != (size_t)msg.len + 1)
    return -EINVAL;

  ret = mutex_lock_interruptible(&dev->tx_lock);
  if (ret)
    return ret;

  while (!tx_has_room(dev, count)) {
    if (dev->stopping) {
      ret = -ENODEV;
      goto out;
    }

    if (iocb->ki_filp->f_flags & O_NONBLOCK) {
      ret = -EAGAIN;
      goto out;
    }

    ret = wait_event_interruptible(dev->tx_wait, tx_has_room(dev, count) || dev->stopping);
    if (ret)
      goto out;
  }

  if (dev->stopping) {
    ret = -ENODEV;
    goto out;
  }

  tx_write_message(dev, &msg);
  ret = count;

 out:
  mutex_unlock(&dev->tx_lock);
  return ret;
}

/* ---------- User read ---------- */
static ssize_t device_driver_read_iter(struct kiocb *iocb, struct iov_iter *to) {
  struct fifo_device *dev = iocb->ki_filp->private_data;

  struct msg_queue *q = &dev->rx_queue;
  struct fifo_msg msg;
  size_t count = iov_iter_count(to);
  size_t bytes;
  int ret;

  ret = mutex_lock_interruptible(&dev->read_lock);
  if (ret)
    return ret;

  while (!queue_has_data(q)) {
    if (dev->stopping) {
      ret = -ENODEV;
      goto out;
    }

    if (iocb->ki_filp->f_flags & O_NONBLOCK) {
      ret = -EAGAIN;
      goto out;
    }

    ret = wait_event_interruptible(q->not_empty, queue_has_data(q) || dev->stopping);
    if (ret)
      goto out;
  }

  /*
   * Peek at the next message before removing it.
   * read_lock ensures no other reader removes it.
   */
  {
    unsigned long flags;

    spin_lock_irqsave(&q->lock, flags);
    msg = q->msgs[q->tail];
    spin_unlock_irqrestore(&q->lock, flags);
  }

  bytes = msg.len + 1;

  if (count < bytes) {
    ret = -EMSGSIZE;
    goto out;
  }

  /*
   * Copy first, dequeue after successful copy.
   * A copy fault must not lose the message.
   */
  if (copy_to_iter(&msg, bytes, to) != bytes) {
    ret = -EFAULT;
    goto out;
  }

  ret = queue_get(q, &msg);
  if (ret)
    goto out;

  /*
   * If RX IRQ was disabled due to queue full,
   * re-enable it here after freeing a slot.
   */
  ret = bytes;

 out:
  mutex_unlock(&dev->read_lock);
  return ret;
}

/* ---------- File operations ---------- */

/*
 * This example assumes a device pointer is stored
 * in inode->i_cdev via an enclosing device structure.
 * open() must set filp->private_data accordingly.
 */
static int device_driver_release(struct inode *inode, struct file *filp) {
  return 0;
}

static const struct file_operations device_driver_fops = {
  .owner      = THIS_MODULE,
  .read_iter  = device_driver_read_iter,
  .write_iter = device_driver_write_iter,
  .release    = device_driver_release,
};

/**

 **/
