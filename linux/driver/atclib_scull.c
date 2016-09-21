/* Copyright (c) 2016, The Linux Foundation. All rights reserved.
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
#include "atclib_scull.h"
 
#define ATCLIB_VERSION "1.0"
#define CLASS_NAME     "at_cman"
#define DEVICE_NAME    "at_cman"
 
struct atclib_control_s {
        dev_t dev_num;
        struct class *dev_class;
        struct device *dev;
};
 
static struct atclib_control_s atclib_ctl;
 
static const char    g_s_Test_string[] = "Hello world from kernel mode!\n\0";
static const ssize_t g_s_Test_size = sizeof(g_s_Test_string);
 
static ssize_t atclib_read(struct file *file_ptr, char __user *user_buffer,
                                size_t count, loff_t *possition)
{
        pr_debug("atclib-driver: Device file is read at offset = %i,
                read bytes count = %u\n", (int)*possition,
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
 
static int atclib_driver_init(void)
{
        int result = 0;
 
        pr_debug("atclib-driver: Initialization started");
        pr_debug("%s: %s version %s\n", __func__, DEVICE_NAME, ATCLIB_VERSION);
 
        atclib_ctl.dev_num = register_chrdev(0, DEVICE_NAME,
                &atclib_driver_fops);
        if (atclib_ctl.dev_num < 0) {
                pr_err("%s: register_chrdev failed\n", __func__);
                goto register_chrdev_err;
       }
 
        atclib_ctl.dev_class = class_create(THIS_MODULE, CLASS_NAME);
        if (IS_ERR(atclib_ctl.dev_class)) {
                pr_err("%s: class_create failed\n", __func__);
                goto class_create_err;
        }
        atclib_ctl.dev = device_create(atclib_ctl.dev_class, NULL,
                                MKDEV(atclib_ctl.dev_num, 0),
                                &atclib_ctl, DEVICE_NAME);
       if (IS_ERR(atclib_ctl.dev)) {
                pr_err("%s: device_create failed\n", __func__);
                goto device_create_err;
        }
        pr_debug("atclib-driver: Initialization completed");
        return result;
 
device_create_err:
        class_destroy(atclib_ctl.dev_class);
class_create_err:
        unregister_chrdev(atclib_ctl.dev_num, DEVICE_NAME);
register_chrdev_err:
        return -ENODEV;
}

static void atclib_driver_exit(void)
{
        pr_debug("%s: Exiting\n", __func__);
        device_unregister(atclib_ctl.dev);
        device_destroy(atclib_ctl.dev_class, MKDEV(atclib_ctl.dev_num, 0));
        class_destroy(atclib_ctl.dev_class);
        unregister_chrdev(atclib_ctl.dev_num, DEVICE_NAME);
}
 
module_init(atclib_driver_init);
module_exit(atclib_driver_exit);
 
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Atul Ruat");
