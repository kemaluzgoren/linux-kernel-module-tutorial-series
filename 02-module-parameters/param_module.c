#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static char *username = "default_name";
static int repeat_count = 1;

module_param(username, charp, S_IRUGO);
MODULE_PARM_DESC(username, "User name to greet");

module_param(repeat_count, int, S_IRUGO);
MODULE_PARM_DESC(repeat_count, "Number of times to greet");

static int __init param_module_init(void)
{
    int i;
    for(i = 0; i < repeat_count; i++) {
        printk(KERN_INFO "[param_module] Hello %s! (%d/%d)\n", username, i+1, repeat_count);
    }
    return 0;
}

static void __exit param_module_exit(void)
{
    printk(KERN_INFO "[param_module] Module removed.\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kemal");
MODULE_DESCRIPTION("Kernel Module with Parameters");

module_init(param_module_init);
module_exit(param_module_exit);
