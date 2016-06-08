/*
Problem : Create a loadable kernel module that initializes a work queue every 500ms.

When the work executes, print a value to dmesg with constantly increments:
[ 8600.899135] atclib_test_workqueue: counter: 18
[ 8601.399947] atclib_test_workqueue: counter: 19
[ 8601.900777] atclib_test_workqueue: counter: 20
[ 8602.401366] atclib_test_workqueue: counter: 21
[ 8602.901998] atclib_test_workqueue: counter: 22
[ 8603.402582] atclib_test_workqueue: counter: 23
[ 8603.903203] atclib_test_workqueue: counter: 24

Create a sysfs node to stop and start the workqueue.
*/

/* Copyright (c) 2016, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/workqueue.h>
#include <linux/kmod.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

static int var;

/* work queue */
static void workq_work_handler(struct work_struct *w);
static struct workqueue_struct *wq;
static DECLARE_DELAYED_WORK(test_work, workq_work_handler);

/* timer */
struct timer_list exp_timer;
static int delay_interval = 50;

static void start_timer(void)
{
	add_timer(&exp_timer);
}

static void stop_timer(void)
{
	if (delay_interval != 0)
		del_timer(&exp_timer);  // del_timer_sync - to avoid race condition occur when del_timer returns it only guarantees that timer is no longer active (
//	means it will no b executed in feature. on smp system timer handler might already be executing on another processor.
//		to deactivate the timer & wait until a potentially executing hander for timer exists use)
}

static void print_message(unsigned long data)
{
	static int val = 1;

	pr_info("ATUL: code_test_workqueue: counter: %d\n", val++);

	start_timer();
}

/* work queue */
static void workq_work_handler(struct work_struct *w)
{
	init_timer_on_stack(&exp_timer);

	exp_timer.expires = (jiffies + delay_interval * HZ);
	exp_timer.data = 0;
	exp_timer.function = print_message;

	start_timer();
}

static ssize_t var_show(struct kobject *kobj, struct kobj_attribute *attr,
			char *buf)
{

	int len;
	char *p = buf;
	len = sizeof(buf);
	return scnprintf(p, len, "%d\n", var);
}

static ssize_t var_store(struct kobject *kobj, struct kobj_attribute *attr,
			 const char *buf, size_t count)
{
	sscanf(buf, "%du", &var);
	if (var == 1)
		start_timer();
	if (var == 0)
		stop_timer();
	return count;
}

static struct kobj_attribute var_attribute =
	__ATTR(var, 0777, var_show, var_store);

static struct attribute *attrs[] = {
	&var_attribute.attr,

	NULL,
};

static struct attribute_group attr_group = {
	.attrs = attrs,
};

static struct kobject *workq_kobj;

static int __init workq_init(void)
{
	int retval;
	unsigned long onesec;
	workq_kobj = kobject_create_and_add("test_workq", kernel_kobj);
	if (!workq_kobj)
		return -ENOMEM;

	retval = sysfs_create_group(workq_kobj, &attr_group);
	if (retval)
		kobject_put(workq_kobj);
	/* work queue */
	onesec = msecs_to_jiffies(500);
	if (!wq)
		wq = create_singlethread_workqueue("workq");
	if (wq)
		queue_delayed_work(wq, &test_work, onesec);
	pr_info("ATUL loaded %u jiffies\n", (unsigned)onesec);
	return retval;
}

static void __exit workq_exit(void)
{
	stop_timer();
	if (wq)
		destroy_workqueue(wq);
	kobject_put(workq_kobj);
}

module_init(workq_init);
module_exit(workq_exit);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Atul Raut <atulraut17@gmail.com>");
