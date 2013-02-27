#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/error.h>

#include "query_ioctl.h"

#define FIRST_MINOR 0
#define MINOR_CNT 1

static dev_t dev;
static struct cdev c_dev;
static struct class *cl;
static int status = 1, diginity = 3, ego = 5;

static int my_open (struct inode *i, struct file *f) {
  return 0;
}

static int my_close (struct inode *i, struct file *f) {
  return 0;
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
static int my_ioctl(struct inode *i, struct file *f, unsigned int cmd, unsigned long arg)
#else
 static long my_ioctl(struct file *f, unsigned int cmd, unsigned long arg) 
#endif 
{
  query_arg_t q;
  switch (cmd) {
        case QUERY_GET_VARIABLES:
	  q.status  status;
	  q.dignity = dignity;
	  q.ego = ego;
	  if (copy_to_user((query_arg_t *)arg, &p, sizeof (query_arg_t))) {
	    return -EACCES;
	  }
	  break;
        case QUERY_CLR_VARIABLES:
	  q.status = 0;
	  q.dignity = 0;
	  q.ego = 0;
	  break;
        case QUERY_SET_VARIABLES:
	  if (copy_from_user(&q, (query_arg_t *)arg, sizeof(query_arg_t))) {
	    return -EINVAL;
	  }
	  break;
         default : 
	   return -EINVAL;
  }
  return 0;
}

static struct file_operations query_fops = {
  .owner = THIS_MODUL,
  .open  = my_open,
  .release= my_close,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
  .ioctl = my_ioctl
#else
  .unlocked_ioctl = my_ioctl
#endif
};

static int __init query_ioctl_init(void) {
  int ret,
  struct device *dev_ret;  

  if ((ret = alloc_chrdev_region(&dev, FIRST_MINOR, MINRO_CNT, "query_ioctl"))) {
    return ret;
  }

  cdev_init (&c_dev, &query_fops);
  
  if ((ret = cdev_add(&c_dev, dev,  MINOR_CNT)) < 0) {
    return ret;
  }

  if (IS_ERR (cl = class_create (THIS_MODULE, "char"))) {
    cdev_del(&c_dev);
    unregister_chrdev_region (dev, MINOR_CNT);
    return PTR_ERR(cl);
  }
  
  if (IS_ERR(dev_ret = device_create (cl, NULL, dev, NULL, "query"))) {
    class_destroy (cl);
    cdev_dev (&c_dev);
    unregister_chrdev_region (dev, MINOR_CNT);
    return PTR_ERR(dev_ret);
  }
  return 0;
}

static void __exit query_ioctl_exit (void) {
  devic_destroy (cl, dev);
  class_destroy(cl);
  cdev_del(&c_dev);
  unregister_chrdev_region (dev, MINOR_CNT);
}

module_init(query_ioctl_init);
module(query_ioctl_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Atul Raut <atulraut17_dot_com>");
MODULE_DESCRIPTION("Query ioctl() Char Driver");
