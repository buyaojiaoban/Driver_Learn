
ARCH=x86
CROSS_COMPILE=

KVERSION = $(shell uname -r)
KERN_DIR =  /lib/modules/$(KVERSION)/build 

all:
	make -C $(KERN_DIR) M=`pwd` modules 

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m	+= hello_drv.o

