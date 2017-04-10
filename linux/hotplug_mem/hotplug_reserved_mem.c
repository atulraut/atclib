/* Hotplug test driver */


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include<linux/sched.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

#include <linux/memblock.h>
#include <linux/bootmem.h>
#include <linux/of.h>
#include <linux/of_address.h>

#define TESTHOTPLUG_BASEADDR 0xC0000000
#define TESTHOTPLUG_MEMSIZE  0x40000000

char *msg = NULL;

/*
 * In order to free reseved memory from bootup we are not
 * able to call the __init free functions, as we could be
 * passed the init boot sequence. As a reult we need to
 * free this memory ourselves using the
 * free_reeserved_page() function.
 */
void testhotplug_free_bootmem(phys_addr_t mem_addr, unsigned long size)
{
	unsigned long pfn_start, pfn_end, pfn_idx;
	pfn_start = mem_addr >> PAGE_SHIFT;
	pfn_end = (mem_addr + size) >> PAGE_SHIFT;
	
	/* Free the reserved page into the buddy system, so it gets managed. */
	for (pfn_idx = pfn_start; pfn_idx < pfn_end; pfn_idx++)
		free_reserved_page(pfn_to_page(pfn_idx));
}

ssize_t read_proc(struct file *filp, char *buf,size_t count, loff_t *offp )
{
	ssize_t ret = 0;

	pr_err("test_hotplug_drv : %s\n", __func__);

	buf[0] = '1';
	buf[1] = 0;
	ret = 2;

	return ret;
}

ssize_t write_proc(struct file *filp,const char __user *buf,size_t count,loff_t *offp)
{
	phys_addr_t hotplug_address = TESTHOTPLUG_BASEADDR;

	pr_err("test_hotplug_drv : %s hotplug_address %pa\n", __func__, &hotplug_address);

	if(copy_from_user(msg,buf,count))
	{
		pr_err("test_hotplug_drv : copy_from_user failed!\n");
		return -1;
	}

	if(hotplug_address == 0)
	{
		return count;
	}

	if(msg[0] == '1')
	{
		pr_err("test_hotplug_drv : write_proc : returning memory 1\n");
		memblock_free(hotplug_address, TESTHOTPLUG_MEMSIZE);
	}
	else if(msg[0] == '2')
	{
		pr_err("test_hotplug_drv : write_proc : returning memory 2\n");
		pr_err("start = %pa len = %lx\n", &hotplug_address, (unsigned long)TESTHOTPLUG_MEMSIZE);
		memblock_free(hotplug_address, TESTHOTPLUG_MEMSIZE);
		testhotplug_free_bootmem(hotplug_address, (unsigned long)TESTHOTPLUG_MEMSIZE);
	}
	else
	{
		pr_err("test_hotplug_drv : write_proc : %c\n",msg[0]);
	}
	return count;
}

struct file_operations proc_fops = {
	.read = read_proc,
	.write = write_proc,
};

void create_new_proc_entry(void)
{
	pr_err("test_hotplug_drv : %s\n", __func__);
	proc_create("test_hotplug", 0, NULL, &proc_fops);
	msg = kmalloc(GFP_KERNEL, 10*sizeof(char));
}

static int __init proc_init(void)
{
	pr_err("test_hotplug_drv : %s\n", __func__);
	create_new_proc_entry();
	return 0;
}

static void __exit proc_cleanup(void)
{
	pr_err("test_hotplug_drv : %s\n", __func__);
	remove_proc_entry("test_hotplug",NULL);
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hotplug Reserved Memory");
module_init(proc_init);
module_exit(proc_cleanup);

