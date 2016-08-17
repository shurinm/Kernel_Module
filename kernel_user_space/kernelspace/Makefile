KERNELDIR:=/usr/src/linux-headers-$(shell uname -r)
PWD := $(shell pwd)
ccflags-y := -std=gnu99
obj-m += kernel_space.o

all:
    sudo $(MAKE) -C $(KERNELDIR) M=$(PWD) modules

install:
    sudo insmod ./kernel_space.ko

delete:
    sudo rmmod kernel_space

clean:
    rm -rf *.o *.ko *.order *.symvers *.mod.c .kernel_space.* .tmp_versions

log:
    sudo vim /var/log/syslog

lclean:
    >/var/log/syslog
