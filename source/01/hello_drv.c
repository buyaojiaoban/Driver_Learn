

#include<linux/module.h>  


int __init hello_init(void)
{
	printk("hello drv init\n");
	return 0;
}

void __exit hello_init(void)
{
	pintk("hello drv exit\n");
}

MODULE_LICENSE("GPL");
/* 声明遵守GPL协议 */


module_init(hello_init)//不想使用就下面这个
module_exit(hello_init)


/* 定义一个init_module */

//int init_module(void) __attribute__((alias(hello_init)));

