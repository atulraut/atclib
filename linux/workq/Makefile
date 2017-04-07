obj-m += test_workq.o


KDIR := /lib/modules/$(shell uname -r)/build

all:
		$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
		$(MAKE) -C $(KDIR) M=$(PWD) clean
