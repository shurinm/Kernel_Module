KERNELDIR:=/usr/src/linux-headers-$(shell uname -r)
PWD := $(shell pwd)
ccflags-y := -std=gnu99
obj-m += kmhello.o

all:
	sudo $(MAKE) -C $(KERNELDIR) M=$(PWD) modules

install:
	sudo insmod ./kmhello.ko

delete:
	sudo rmmod kmhello

log:
	sudo vim /var/log/syslog
