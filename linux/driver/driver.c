/*
* Learning Driver
* http://www.linuxforu.com/2010/12/writing-your-first-linux-driver/
* Date : Thursday April 05, 2012.
***/
/* ofd.c - Our First Driver Code*/

#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>

/* Constructor : */
static int __init ofd_init (void) {
	printk (KERN_INFO "Ram Ram : Ofd registered. !");
}

/* Destructor : */
static void __exit ofd_exit (void) {
	printk (KERN_INFO "Good Bye : Ofd unregistered. !");
}

module_init (ofd_init);
module_exit (ofd_exit);

MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("Atul Raut <atulraut17@gmail-dotcom>");
MODULE_DESCRIPTION ("ATUL'S FIRST DRIVER");
