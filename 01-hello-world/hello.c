#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kemal Uzgören");
MODULE_DESCRIPTION("Simple Hello World Kernel Module");

static int __init hello_init(void)
{
    printk(KERN_INFO "[Hello Kernel] Module Loaded!\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "[Hello Kernel] Module Removed!\n");
}

module_init(hello_init);
module_exit(hello_exit);
