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
#ifndef _CPU_HOTPLUG_H
#define _CPU_HOTPLUG_H

#include <linux/io.h>
#include <linux/ioctl.h>

struct early_resources {
    const char  *name;
    int     id;
    struct device   dev;
    struct resource *ctl_mem;
    struct resource *ctl_io;
    const struct platform_device_id *id_entry;
    void __iomem  *lk_virtbase;  /* lk_virtbase for memory mapping */
};

typedef struct early_arg_t {
  unsigned int cpu_num;
} early_arg;

#define EARLY_BASE_MAGIC 'q'

/* ioctls and their arguments */
#define EARLY_SERVICES_WRITE _IOW(EARLY_BASE_MAGIC, 1, early_arg *)
#define EARLY_SERVICES_READ _IOWR(EARLY_BASE_MAGIC, 2, early_arg *)

#endif
