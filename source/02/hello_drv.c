
#include<linux/module.h>
#include <linux/fs.h>


static int major = 0;
static struct file_operations hello_fops = {	
	.owner = THIS_MODULE,
	
};



int __init hello_init(void)
{
	printk("hello drv init\n");
	major = register_chrdev(0, "hello_drv", &hello_fops);
	return 0;
}

void __exit hello_exit(void)
{
	printk("hello drv exit\n");
	unregister_chrdev(major, "hello_drv");
}

/* 声明遵守GPL协议 */


module_init(hello_init);//不想使用就下面这个
module_exit(hello_exit);
MODULE_LICENSE("GPL");


/* 定义一个init_module */

//int init_module(void) __attribute__((alias(hello_init)));

