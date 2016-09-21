# Makefile - makefile of our first driver

# if KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can used its language.

ifneq (${KERNELRELEASE},)
	obj-m := atclib_scull.o
# Otherwise we were called directly from the command line.
# Invoke the kernel build system.
else 
	KERNEL_SOURCE := /usr/src/linux/
	PWD := $(shell pwd)
default :
	${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} modules

clean :
	${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} clean
endif
