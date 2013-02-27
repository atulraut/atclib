# If called directly from the command line, invoke the kernel build system.
ifeq ($(KERNELRELEASE),)
    KERNEL_SOURCE := /usr/src/linux
    PWD := $(shell pwd)
default: module query_app

module:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=$(PWD) clean
	${RM} query_app

# Otherwise KERNELRELEASE is defined; we've been invoked from the
# kernel build system and can use its language.
else

    obj-m := query_ioctl.o

endif
