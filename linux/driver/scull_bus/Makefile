#CFLAGS_atclib_task_5.o = -DDEBUG

obj-m += atclib_scull.o
KDIR := /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

all:
		$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
		$(MAKE) -C $(KDIR) M=$(PWD) clean
