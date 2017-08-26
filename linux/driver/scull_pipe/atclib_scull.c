/*
 * Copyright (C) 2001 Alessandro Rubini and Jonathan Corbet
 * Copyright (C) 2001 O'Reilly & Associates
 * Copyright (c) 2016, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
*/

#include <linux/init.h>   /* module_init, module_exit */
#include <linux/fs.h>     /* file stuff */
#include <linux/kernel.h> /* printk() */
#include <linux/errno.h>  /* error codes */
#include <linux/module.h>   /* THIS_MODULE */
#include <linux/cdev.h>     /* char device stuff */
#include <linux/uaccess.h>  /* copy_to_user() */
#include <linux/module.h>   /* version info, MODULE_AUTHOR, printk() */
#include <linux/device.h>   /* class_create */
#include <linux/slab.h>     /* kmalloc */
#include "atclib_scull.h"

#define ATCLIB_VERSION "1.0"
#define CLASS_NAME     "atclib_class"
#define DEVICE_NAME    "atclib"
int scull_major =   SCULL_MAJOR;
int scull_minor =   0;
int scull_nr_devs = SCULL_NR_DEVS;/* number of bare scull devices */
int scull_quantum = SCULL_QUANTUM;
int scull_qset    = SCULL_QSET;

static struct atclib_dev *atclib_devices;
static struct class *atclib_class;

/*
* Empty out the scull device; must be called with the device
* semaphore held.
*/
int atclib_trim(struct atclib_dev *dev)
{
	struct scull_qset *next, *dptr;
	int qset = dev->qset;   /* "dev" is not-null */
	int i;

	for (dptr = dev->data; dptr; dptr = next) { /* all the list items */
		if (dptr->data) {
			for (i = 0; i < qset; i++)
				kfree(dptr->data[i]);
			kfree(dptr->data);
			dptr->data = NULL;
		}
	next = dptr->next;
	kfree(dptr);
	}
	dev->size = 0;
	dev->quantum = scull_quantum;
	dev->qset = scull_qset;
	dev->data = NULL;
	return 0;
}

/*
 * Open and close
 */

int atclib_open(struct inode *inode, struct file *filp)
{
	struct atclib_dev *dev; /* device information */

	dev = container_of(inode->i_cdev, struct atclib_dev, cdev);
	filp->private_data = dev; /* for other methods */

/* now trim to 0 the length of the device if open was write-only */
	if ((filp->f_flags & O_ACCMODE) == O_WRONLY) {
		if (mutex_lock_interruptible(&dev->mutex))
			return -ERESTARTSYS;
		atclib_trim(dev); /* ignore errors */
		mutex_unlock(&dev->mutex);
	}
	return 0;          /* success */
}

int atclib_release(struct inode *inode, struct file *filp)
{
	return 0;
}
/*
 * Follow the list
 */
struct scull_qset *atclib_follow(struct atclib_dev *dev, int n)
{
	struct scull_qset *qs = dev->data;

	/* Allocate first qset explicitly if need be */
	if (!qs) {
		qs = dev->data = kmalloc(sizeof(struct scull_qset), GFP_KERNEL);
		if (qs == NULL)
			return NULL;  /* Never mind */
		memset(qs, 0, sizeof(struct scull_qset));
	}

	/* Then follow the list */
	while (n--) {
		if (!qs->next) {
			qs->next = kmalloc(sizeof(struct scull_qset),
				GFP_KERNEL);
			if (qs->next == NULL)
				return NULL;  /* Never mind */
			memset(qs->next, 0, sizeof(struct scull_qset));
		}
		qs = qs->next;
		continue;
	}
	return qs;
}

ssize_t atclib_write(struct file *filp, const char __user *buf, size_t count,
		    loff_t *f_pos)
{
	struct atclib_dev *dev = filp->private_data;
	struct scull_qset *dptr;
	int quantum = dev->quantum, qset = dev->qset;
	int itemsize = quantum * qset;
	int item, s_pos, q_pos, rest;
	ssize_t retval = -ENOMEM; /* value used in "goto out" statements */

	if (mutex_lock_interruptible(&dev->mutex))
		return -ERESTARTSYS;

	/* find listitem, qset index and offset in the quantum */
	item = (long)*f_pos / itemsize;
	rest = (long)*f_pos % itemsize;
	s_pos = rest / quantum; q_pos = rest % quantum;

	/* follow the list up to the right position */
	dptr = atclib_follow(dev, item);
	if (dptr == NULL)
		goto out;
	if (!dptr->data) {
		dptr->data = kmalloc(qset *
			sizeof(char *), GFP_KERNEL);
		if (!dptr->data)
			goto out;
		memset(dptr->data, 0, qset * sizeof(char *));
	}
	if (!dptr->data[s_pos]) {
		dptr->data[s_pos] = kmalloc(quantum, GFP_KERNEL);
		if (!dptr->data[s_pos])
			goto out;
	}
	/* write only up to the end of this quantum */
	if (count > quantum - q_pos)
		count = quantum - q_pos;

	if (copy_from_user(dptr->data[s_pos]+q_pos, buf, count)) {
		retval = -EFAULT;
		goto out;
	}
	*f_pos += count;
	retval = count;

	/* update the size */
	if (dev->size < *f_pos)
		dev->size = *f_pos;

out:
	mutex_unlock(&dev->mutex);
	return retval;
}


ssize_t atclib_read(struct file *filp, char __user *buf, size_t count,
		   loff_t *f_pos)
{
	struct atclib_dev *dev = filp->private_data;
	struct scull_qset *dptr;/* the first listitem */
	int quantum = dev->quantum, qset = dev->qset;
	int itemsize = quantum * qset; /* how many bytes in the listitem */
	int item, s_pos, q_pos, rest;
	ssize_t retval = 0;

	if (mutex_lock_interruptible(&dev->mutex))
		return -ERESTARTSYS;
	if (*f_pos >= dev->size)
		goto out;
	if (*f_pos + count > dev->size)
		count = dev->size - *f_pos;

	/* find listitem, qset index, and offset in the quantum */
	item = (long)*f_pos / itemsize;
	rest = (long)*f_pos % itemsize;
	s_pos = rest / quantum; q_pos = rest % quantum;

	/* follow the list up to the right position (defined elsewhere) */
	dptr = atclib_follow(dev, item);

	if (dptr == NULL || !dptr->data || !dptr->data[s_pos])
		goto out; /* don't fill holes */

	/* read only up to the end of this quantum */
	if (count > quantum - q_pos)
		count = quantum - q_pos;

	if (copy_to_user(buf, dptr->data[s_pos] + q_pos, count)) {
		retval = -EFAULT;
	goto out;
	}
	*f_pos += count;
	retval = count;

out:
	mutex_unlock(&dev->mutex);
	return retval;
}

/*
 * The ioctl() implementation
 */

long atclib_ioctl(struct file *filp,
			unsigned int cmd, unsigned long arg)
{
	int err = 0, tmp;
	int retval = 0;

  /*
   * extract the type and number bitfields, and don't decode
   * wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok()
   */
	if (_IOC_TYPE(cmd) != SCULL_IOC_MAGIC)
		return -ENOTTY;
	if (_IOC_NR(cmd) > SCULL_IOC_MAXNR)
		return -ENOTTY;

  /*
   * the direction is a bitmask, and VERIFY_WRITE catches R/W
   * transfers. `Type' is user-oriented, while
   * access_ok is kernel-oriented, so the concept of "read" and
   * "write" is reversed
   */
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user *)arg,
			_IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err =  !access_ok(VERIFY_READ, (void __user *)arg,
			_IOC_SIZE(cmd));
	if (err)
		return -EFAULT;

	switch (cmd) {
	case SCULL_IOCRESET:
		scull_quantum = SCULL_QUANTUM;
		scull_qset = SCULL_QSET;
		break;

	case SCULL_IOCSQUANTUM: /* Set: arg points to the value */
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		retval = __get_user(scull_quantum, (int __user *)arg);
		break;

	case SCULL_IOCTQUANTUM: /* Tell: arg is the value */
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		scull_quantum = arg;
		break;

	case SCULL_IOCGQUANTUM: /* Get: arg is pointer to result */
		retval = __put_user(scull_quantum, (int __user *)arg);
		break;

	case SCULL_IOCQQUANTUM: /* Query: return it (it's positive) */
		return scull_quantum;

	case SCULL_IOCXQUANTUM: /* eXchange: use arg as pointer */
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		tmp = scull_quantum;
		retval = __get_user(scull_quantum, (int __user *)arg);
		if (retval == 0)
			retval = __put_user(tmp, (int __user *)arg);
		break;

	case SCULL_IOCHQUANTUM: /* sHift: like Tell + Query */
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		tmp = scull_quantum;
		scull_quantum = arg;
		return tmp;

	case SCULL_IOCSQSET:
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		retval = __get_user(scull_qset, (int __user *)arg);
		break;

	case SCULL_IOCTQSET:
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		scull_qset = arg;
		break;

	case SCULL_IOCGQSET:
		retval = __put_user(scull_qset, (int __user *)arg);
	break;

	case SCULL_IOCQQSET:
		return scull_qset;

	case SCULL_IOCXQSET:
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		tmp = scull_qset;
		retval = __get_user(scull_qset, (int __user *)arg);
		if (retval == 0)
			retval = put_user(tmp, (int __user *)arg);
		break;

	case SCULL_IOCHQSET:
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		tmp = scull_qset;
		scull_qset = arg;
		return tmp;

    /*
     * The following two change the buffer size for scullpipe.
     * The scullpipe device uses this same ioctl method, just to
     * write less code. Actually, it's the same driver, isn't it?
     */

	case SCULL_P_IOCTSIZE:
		scull_p_buffer = arg;
		break;

	case SCULL_P_IOCQSIZE:
		return scull_p_buffer;

	default:  /* redundant, as cmd was checked against MAXNR */
		return -ENOTTY;
	}
	return retval;
}

/*
 * The "extended" operations -- only seek
 */

loff_t atclib_llseek(struct file *filp, loff_t off, int whence)
{
	struct atclib_dev *dev = filp->private_data;
	loff_t newpos;

	switch (whence) {
	case 0: /* SEEK_SET */
		newpos = off;
		break;

	case 1: /* SEEK_CUR */
		newpos = filp->f_pos + off;
		break;

	case 2: /* SEEK_END */
		newpos = dev->size + off;
		break;

	default: /* can't happen */
		return -EINVAL;
	}
	if (newpos < 0)
		return -EINVAL;
	filp->f_pos = newpos;
	return newpos;
}

const struct file_operations atclib_driver_fops = {
	.owner =    THIS_MODULE,
	.llseek =   atclib_llseek,
	.read =     atclib_read,
	.write =    atclib_write,
	.unlocked_ioctl = atclib_ioctl,
	.open =     atclib_open,
	.release =  atclib_release,
};

/* remove char deivces if exist */
static void atclib_exit_module(int devices_to_destroy)
{
	int i;
	if (atclib_devices) {
		for (i = 0; i < devices_to_destroy; ++i) {
			BUG_ON(NULL == &atclib_devices[i] ||
					NULL == atclib_class);
			device_destroy(atclib_class, MKDEV(scull_major, i));
			atclib_trim(atclib_devices + i);
			cdev_del(&atclib_devices[i].cdev);
			mutex_destroy(&atclib_devices[i].mutex);
		}
		kfree(atclib_devices);
	}
	if (atclib_class)
		class_destroy(atclib_class);
	unregister_chrdev_region(MKDEV(scull_major, 0), scull_nr_devs);
	pr_err ("atclib: atclib_scull resources got clean up!");
}

/* Initialize each device. */
static int atclib_construct_device(struct atclib_dev *atclib_devices, int minor,
		       struct class *class)
{
	struct device *device = NULL;  /*device to registers with sysfs*/
	dev_t curr_dev = 0;
	int ret = 0;

	/* Build up the current device number. To be used further */
	scull_minor = curr_dev = MKDEV(scull_major, minor);
	pr_info("atclib: major=%d minor = %d", scull_major, curr_dev);

	atclib_devices->quantum = scull_quantum;
	atclib_devices->qset = scull_qset;
	mutex_init(&atclib_devices->mutex);

	/* Associate the cdev with a set of file_operations */
	cdev_init(&atclib_devices->cdev, &atclib_driver_fops);
	atclib_devices->cdev.owner = THIS_MODULE;

	/* Now make the device live for the users to access */
	cdev_add(&atclib_devices->cdev, curr_dev, 1);

	/* Create a device node for this device. Look, the class is
	* being used here. The same class is associated with N_MINOR
	* devices. Once the function returns, device nodes will be
	* created as /dev/atclib0, /dev/atclib1,...
	* You can also view the devices under /sys/class/atclib_class
	*/
	device = device_create(class, NULL,
					curr_dev,
					NULL, DEVICE_NAME"%d", minor);
	if (IS_ERR(device)) {
		pr_err("%s: device_create failed\n", __func__);
		ret = PTR_ERR(device);
		cdev_del(&atclib_devices->cdev);
		return ret;
	}
	return ret;
}

static int atclib_driver_init(void)
{
	dev_t curr_dev = 0;
	int result = 0;
	int devices_to_destroy = 0;
	int i = 0;

	pr_info("atclib_driver: Initialization started");
	pr_info("%s: %s version %s\n", __func__, DEVICE_NAME, ATCLIB_VERSION);
/*
* Get a range of minor numbers to work with, asking for a dynamic
* major.
*/
	if (scull_major) {
		curr_dev = MKDEV(scull_major, scull_minor);
		result = register_chrdev_region(curr_dev,
				scull_nr_devs, DEVICE_NAME);
	} else {
		result = alloc_chrdev_region(&curr_dev,
				scull_minor, scull_nr_devs,
				DEVICE_NAME);
		scull_major = MAJOR(curr_dev);
	}
	if (result < 0) {
		pr_info("atclib: can't get major %d\n", scull_major);
		return result;
	}

/*
	* allocate the devices -- we can't have them static, as the number
	* can be specified at load time
	*/
	atclib_devices = kmalloc(scull_nr_devs *
			sizeof(struct atclib_dev), GFP_KERNEL);
	if (!atclib_devices) {
		result = -ENOMEM;
		goto fail;  /* Make this more graceful */
	}
	memset(atclib_devices, 0, scull_nr_devs * sizeof(struct atclib_dev));

	atclib_class = class_create(THIS_MODULE, CLASS_NAME);
	if (IS_ERR(atclib_class)) {
		pr_err("%s: class_create failed\n", __func__);
		goto fail;
	}

	/* Construct devices */
	for (i = 0; i < scull_nr_devs; ++i) {
		result = atclib_construct_device(&atclib_devices[i],
				i, atclib_class);
		if (result) {
			devices_to_destroy = i;
			goto fail;
		}
	}
	pr_info("atclib-driver: Initialization completed !");
	/* At this point call the init function for any friend device */
	curr_dev = MKDEV(scull_major, scull_minor+ 1 + scull_nr_devs);
	curr_dev += scull_p_init(curr_dev);
	pr_info("atclib: Initialization completed !");
	return result;

fail:
	atclib_exit_module(devices_to_destroy);
	return -ENODEV;
}

static void atclib_driver_exit(void)
{
	atclib_exit_module(scull_nr_devs);
	scull_p_cleanup ();
}

module_init(atclib_driver_init);
module_exit(atclib_driver_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Atul Raut");
