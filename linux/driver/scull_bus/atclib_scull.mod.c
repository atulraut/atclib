#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x7799aa3d, "module_layout" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0xecea79ab, "device_create" },
	{ 0x9ed5f8e8, "cdev_add" },
	{ 0xf9dc1554, "cdev_init" },
	{ 0xc695b60e, "__mutex_init" },
	{ 0xfec088ad, "__class_create" },
	{ 0xd8e484f0, "register_chrdev_region" },
	{ 0x27e1a049, "printk" },
	{ 0xde0bdcff, "memset" },
	{ 0x5a34a45c, "__kmalloc" },
	{ 0x4f6b400b, "_copy_from_user" },
	{ 0x4f8b5ddb, "_copy_to_user" },
	{ 0x86bfe20c, "kmem_cache_alloc_trace" },
	{ 0x972d523a, "kmalloc_caches" },
	{ 0xd22651e6, "mutex_unlock" },
	{ 0x91f848ac, "mutex_lock_interruptible" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x65a3da7e, "class_destroy" },
	{ 0x93b4bd0a, "cdev_del" },
	{ 0x901fdb5b, "device_destroy" },
	{ 0x37a0cba, "kfree" },
	{ 0xb2fd5ceb, "__put_user_4" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xc6cbbc89, "capable" },
	{ 0x4c4fef19, "kernel_stack" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "6984F512A14CD92ACA1537B");
