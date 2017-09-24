
obj-m	+= lddbus.o 
obj-m   += atclib_scull_devices.o

#scullbus-objs := lddbus.o
#sculldrv-objs := ldddrv.o 

KDIR := /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

all:
		$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
		$(MAKE) -C $(KDIR) M=$(PWD) clean
