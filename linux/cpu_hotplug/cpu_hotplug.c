/* Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/version.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cpu.h>
#include <asm/cpu_ops.h>
#include <linux/moduleparam.h>
#include <linux/cpumask.h>
#include <linux/cpufreq.h>
#include <linux/smp.h>
#include <soc/qcom/spm.h>
#include <soc/qcom/pm.h>
#include <asm/suspend.h>
#include <asm/cacheflush.h>
#include <asm/cputype.h>
#include <asm/system_misc.h>

#include "cpu_hotplug.h"

#define DRIVER_NAME "cpu_hotplug"
#define CPU_COUNT 10

static int ctl_cpu_hotplug(unsigned int cpu_num)
{
  int ret = 0;
  pr_err ("%s: early_services: Hotplug started \n", __func__);
  lock_device_hotplug();
  ret = device_online(get_cpu_device(cpu_num));
  unlock_device_hotplug();
  if (ret) {
    pr_err("%s: early_services: CPU hotplug : [%d] failed\n", __func__, cpu_num);
  } else
    pr_err("%s: early_services: CPU [%d] got hotpluged sucessfully. \n", __func__, cpu_num);
  return ret;
}

static ssize_t write_cpuinfo(struct file *file, const char __user *buf,
				 size_t count, loff_t *ppos)
{
  char lbuf[CPU_COUNT] = {0};
  uint64_t seq_num = 0;
  int ret = 0;
  if (copy_from_user(lbuf, buf, sizeof(lbuf)))
    return -EFAULT;
  ret = sscanf(lbuf, "%llu", &seq_num);
  if (ret != 1)
    pr_err("%s: (Kernel): Bad or malformed sequence number\n", __func__);
  else
    pr_debug("%s: (Kernel): seq_num = %llu\n", __func__, seq_num);
  if (seq_num > 4 && seq_num < 0)
      return -EINVAL;
  pr_err("%s : early_services user Input = %llu \n", __func__ , seq_num);
  ctl_cpu_hotplug((unsigned int)seq_num);

  return count;
}

static long early_services_ioctl(struct file *f, unsigned int cmd,
				 unsigned long arg)
{
  early_arg val;
  switch (cmd) {
  case EARLY_SERVICES_WRITE:
    if (copy_from_user(&val, (early_arg *) arg,
		       sizeof(early_arg)));
    return -EACCES;
    if (val.cpu_num > 4 && val.cpu_num < 0)
      return -EINVAL;
    pr_err("%s : user Input = %d \n", __func__ , val.cpu_num);
    ctl_cpu_hotplug(val.cpu_num);
    break;
  case EARLY_SERVICES_READ:
    if (copy_from_user(&val, (early_arg *) arg,
		       sizeof(early_arg)));
    return -EACCES;
    if  (val.cpu_num > 4 && val.cpu_num < 0)
      return -EINVAL;
    //    val.cpu_num = ;
    if (copy_to_user((early_arg *) arg, &val,
		     sizeof(early_arg)));
    return -EACCES;
    break;
  default: return -EINVAL;
  }
}

static void early_services_online_action(unsigned int cpu) {
  pr_err("%s : early_services:  online cpu = %u \n", __func__ , cpu);
}

static void early_services_dead_action(unsigned int cpu) {
  pr_err("%s : early_services: offline cpu = %u  \n", __func__ ,cpu);
}

static int early_services_cpu_callback(struct notifier_block *nfb,
				unsigned long action, void *hcpu)
{
  unsigned int cpu = (unsigned long)hcpu;

  switch (action) {
  case CPU_ONLINE:
  case CPU_ONLINE_FROZEN:
    early_services_online_action(cpu);
    break;
  case CPU_DEAD:
  case CPU_DEAD_FROZEN:
    early_services_dead_action(cpu);
    break;
  }
  return NOTIFY_OK;
}

static int early_services_resource_init(struct platform_device *pdev,
        struct early_resources *alk_res)
{
  u8 val = 0;

  if (!pdev || !alk_res) {
    pr_err("Invalid input parameters\n");
    return -EINVAL;
  }

  val = ioread8(alk_res->lk_virtbase);
  pr_err("%s: early_services: Kernel Reading updated register val = %x \n", __func__, (u8)val);
  return 0;
}

static void early_services_resource_deinit(struct platform_device *pdev,
				   struct early_resources *alk_res)
{
  if (!pdev || !alk_res) {
    pr_err("Invalid input parameters\n");
    return;
  }
}

static void early_services_resource_release(struct platform_device *pdev,
				    struct early_resources *alk_res)
{
  if (!pdev || !alk_res) {
    pr_err("Invalid input parameters\n");
    return;
  }
}

static const struct file_operations early_services_fops = {
    .owner = THIS_MODULE,
    .write = write_cpuinfo,
    .unlocked_ioctl = early_services_ioctl,
};

static struct  miscdevice early_services_misc_device = {
  .minor = MISC_DYNAMIC_MINOR,
  .name  = DRIVER_NAME,
  .fops = &early_services_fops,
};

static int early_services_probe(struct platform_device *pdev)
{
  int rc = 0;
  const char *label;
  struct early_resources *lk_res;

  pr_info("%s: early_services_probe called. \n", __func__);

  /* register ourselfs as misc device: creates /dev/early_services*/
  rc = misc_register(&early_services_misc_device);

  /* find registers in device treee; verify availability  */
  if (!pdev->dev.of_node) {
    pr_err("early_services driver only supports device tree probe\n");
    rc = -ENOTSUPP;
    goto error;
  }

  label = of_get_property(pdev->dev.of_node, "label", NULL);
  if (!label)
    pr_info("%s: %d: early_services label not specified\n",__func__,  __LINE__);
  else
    pr_info("%s: early_ services label = %s\n",__func__, label);

  lk_res = devm_kzalloc(&pdev->dev, sizeof(struct early_resources),
			GFP_KERNEL);
  if (!lk_res) {
    pr_err("Failed to allocate the resources for early_services\n");
    rc = -ENOMEM;
    goto error;
  }

  platform_set_drvdata(pdev, lk_res);

  /* manage I/O registers/memory using kernel resource struct */
  lk_res->ctl_mem = platform_get_resource_byname(pdev,
						 IORESOURCE_MEM, "lk_base");
  if (!lk_res->ctl_mem) {
    pr_err("Unable to get the early_services base resources\n");
    rc = -ENOMEM;
    goto io_error;
  }

  /* I/O memory regions must be allocated prior to use */
  lk_res->ctl_io = request_mem_region(lk_res->ctl_mem->start,
				      resource_size(lk_res->ctl_mem), pdev->name);

  if (!lk_res->ctl_io) {
    pr_err("%s: early_services: no valid mem region\n", __func__);
    rc = -EBUSY;
    goto io_error;
  }

  /* mapping I/O memroy nocache for Lk to have easy access,
   * assign virtual addresses to I/O memory regions */
  lk_res->lk_virtbase = ioremap_nocache(lk_res->ctl_mem->start,
			    resource_size(lk_res->ctl_mem));

  if (!lk_res->lk_virtbase) {
    pr_err("Unable to remap early_services resources\n");
    rc = -ENOMEM;
    goto io_error;
  }

  rc = early_services_resource_init(pdev, lk_res);
  if (rc) {
    pr_err("early_services resource init failed rc=%d\n", rc);
    goto res_init_error;
  }
  return rc;

 res_init_error:
  if (lk_res->lk_virtbase)
    iounmap(lk_res->lk_virtbase);
 io_error:
  platform_set_drvdata (pdev, NULL);
  devm_kfree(&pdev->dev, lk_res);
 error:
  return rc;
}

static int early_services_remove(struct platform_device *pdev)
{
  struct early_resources *lk_res;

  lk_res = platform_get_drvdata(pdev);
  if (!lk_res) {
    pr_err("Invalid resource data");
    return 0;
  }

  early_services_resource_deinit(pdev, lk_res);
  early_services_resource_release(pdev, lk_res);
  if (lk_res->lk_virtbase)
    iounmap(lk_res->lk_virtbase);
  release_mem_region(lk_res->ctl_mem->start, resource_size(lk_res->ctl_mem));
  platform_set_drvdata (pdev, NULL);
  devm_kfree(&pdev->dev, lk_res);
  misc_deregister (&early_services_misc_device);
  return 0;
}

static struct notifier_block early_services_cpu_notifier =
  {
    .notifier_call = early_services_cpu_callback,
  };

/* Table of "compatible" values to search for */
static const struct of_device_id early_services_of_match[] = {
  {.compatible = "qcom,shared-early-pool"},
  {},
};
MODULE_DEVICE_TABLE(of, early_services_of_match);

/* Platform device info */
static struct platform_driver early_services_driver = {
  .probe = early_services_probe,
  .remove = early_services_remove,
  .driver = {
    .name = "early_base",
    .owner  = THIS_MODULE,
    .of_match_table = of_match_ptr(early_services_of_match),
  },
};

static int __init early_services_driver_init(void)
{
  int rc = 0;
  register_cpu_notifier(&early_services_cpu_notifier);

  rc = platform_driver_register(&early_services_driver);
  if (rc)
    pr_err("early_services_driver_init() failed!\n");
  return rc;
}

static void __exit early_services_driver_deinit(void)
{
  platform_driver_unregister(&early_services_driver);
}

module_init(early_services_driver_init);
module_exit(early_services_driver_deinit);

MODULE_DESCRIPTION("cpu hotplug driver");
MODULE_LICENSE("GPL v2");
