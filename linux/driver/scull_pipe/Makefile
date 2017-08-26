
obj-m	+= scull.o

scull-objs := atclib_scull.o atclib_pipe.o 

KDIR := /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

all:
		$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
		$(MAKE) -C $(KDIR) M=$(PWD) clean
