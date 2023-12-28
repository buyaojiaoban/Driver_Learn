#include <linux/capability.h>
#include <linux/errno.h>
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <linux/init.h>
#include <linux/ipx.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/net.h>
#include <linux/netdevice.h>
#include <linux/uio.h>
#include <linux/slab.h>
#include <linux/skbuff.h>
#include <linux/socket.h>
#include <linux/sockios.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/termios.h>
#include <linux/device.h>



#include<linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

static int major = 0;
static int ker_val = 123;
static struct class *class_for_hello;

static ssize_t hello_read (struct file *file, char __user *buf, size_t size, loff_t *offset)
{
	int err;
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	copy_to_user(buf, &ker_val, 4);
	return 4;
}

static ssize_t hello_write (struct file *file, const char __user *buf, size_t size, loff_t *offset)
{
	int err;
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	copy_from_user(&ker_val, buf, 4);
	return 4;
}

static struct file_operations hello_fops = {	
	.owner = THIS_MODULE,
	.read  = hello_read,
	.write  = hello_write,	
};



int __init hello_init(void)
{
	printk("hello drv init\n");
	major = register_chrdev(0, "hello_drv", &hello_fops);
	class_for_hello = class_create(THIS_MODULE, "hello_class");
	device_create(class_for_hello, NULL, MKDEV(major, 0), NULL, "myhello"); /* /dev/myhello */
	return 0;
}

void __exit hello_exit(void)
{
	printk("hello drv exit\n");
	device_destroy(class_for_hello, MKDEV(major, 0));
	class_destroy(class_for_hello);
	unregister_chrdev(major, "hello_drv");
}

/* 声明遵守GPL协议 */


module_init(hello_init);//不想使用就下面这个
module_exit(hello_exit);
MODULE_LICENSE("GPL");


/* 定义一个init_module */

//int init_module(void) __attribute__((alias(hello_init)));

