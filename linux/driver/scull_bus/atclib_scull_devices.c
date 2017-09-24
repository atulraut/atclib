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
 * This driver create four char devices /dev/atclib0,1,2,3	
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

static const char    g_s_Test_string[] = "Hello world from kernel mode!\n\0";
static const ssize_t g_s_Test_size = sizeof(g_s_Test_string);

static ssize_t atclib_read(struct file *file_ptr, char __user *user_buffer,
				size_t count, loff_t *possition)
{
	pr_debug("atclib: read offset = %i, read bytes = %u\n", (int)*possition,
		(unsigned int)count);

	if (*possition >= g_s_Test_size)
		return 0;

	if (*possition + count > g_s_Test_size)
		count = g_s_Test_size - *possition;

	if (copy_to_user(user_buffer, g_s_Test_string + *possition, count) != 0)
		return -EFAULT;

	*possition += count;
	return count;
}

const struct file_operations atclib_driver_fops = {
	.owner =    THIS_MODULE,
	/*.llseek =   scull_llseek,*/
	.read =     atclib_read,
	/*   .write =    scull_write,
	.unlocked_ioctl =    scull_ioctl,
	.open =     scull_open,
	.release =  scull_release, */
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
			cdev_del(&atclib_devices[i].cdev);
			mutex_destroy(&atclib_devices[i].mutex);
		}
		kfree(atclib_devices);
	}
	if (atclib_class)
		class_destroy(atclib_class);
        unregister_ldd_driver(&sculld_driver);
	unregister_chrdev_region(MKDEV(scull_major, 0), scull_nr_devs);
}

/* Initialize each device. */
static int atclib_construct_device(struct atclib_dev *atclib_devices, int minor,
		       struct class *class)
{
	struct device *device = NULL;  /*device to registers with sysfs*/
	dev_t curr_dev = 0;
	int ret = 0;

	/* Build up the current device number. To be used further */
	curr_dev = MKDEV(scull_major, minor);
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
	* created as /dev/atclib_scull0, /dev/atclib_scull1,...
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

static int sculld_register_dev(struct atclib_dev *dev, int index) {
        int ret = -1;
	sprintf(dev->devname, "atclib%d", index);
	dev->ldev.name = dev->devname;
	dev->ldev.driver = &sculld_driver;
	dev->ldev.dev.driver_data = dev;
	ret = register_ldd_device(&dev->ldev);
	//	device_create_file(&dev->ldev.dev, &dev_attr_dev);
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
	 * Register with the driver core.
	 */
	register_ldd_driver(&sculld_driver);

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
		result = sculld_register_dev(&atclib_devices[i], i);
		if (result) {
			devices_to_destroy = i;
			goto fail;
		}
	}
	pr_info("atclib-driver: Initialization completed !");
	return result;

fail:
	atclib_exit_module(devices_to_destroy);
	return -ENODEV;
}

static void atclib_driver_exit(void)
{
	atclib_exit_module(scull_nr_devs);
}

module_init(atclib_driver_init);
module_exit(atclib_driver_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Atul Raut");
