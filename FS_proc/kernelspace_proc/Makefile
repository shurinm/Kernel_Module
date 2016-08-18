KERNELDIR:=/usr/src/linux-headers-$(shell uname -r)
PWD := $(shell pwd)
ccflags-y := -std=gnu99
obj-m += fs_proc.o

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

install:
	insmod ./fs_proc.ko

delete:
	rmmod fs_proc

clean:
	rm -rf *.o *.ko *.order *.symvers *.mod.c .fs_proc.* .tmp_versions

log:
	vim /var/log/syslog

lclean:
	>/var/log/syslog
