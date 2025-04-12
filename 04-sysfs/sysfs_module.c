#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/string.h>

static struct kobject *my_kobj;
static char my_value[100] = "default";

static ssize_t my_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%s\n", my_value);
}

static ssize_t my_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    snprintf(my_value, sizeof(my_value), "%s", buf);
    return count;
}

static struct kobj_attribute my_attr = __ATTR(myvalue, 0660, my_show, my_store);

static int __init sysfs_module_init(void)
{
    my_kobj = kobject_create_and_add("my_sysfs", kernel_kobj);
    if (!my_kobj)
        return -ENOMEM;

    if (sysfs_create_file(my_kobj, &my_attr.attr))
        return -ENOMEM;

    printk(KERN_INFO "[sysfs_module] /sys/kernel/my_sysfs/myvalue created\n");
    return 0;
}

static void __exit sysfs_module_exit(void)
{
    sysfs_remove_file(my_kobj, &my_attr.attr);
    kobject_put(my_kobj);
    printk(KERN_INFO "[sysfs_module] sysfs entry removed\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kemal");
MODULE_DESCRIPTION("Kernel Module using sysfs");

module_init(sysfs_module_init);
module_exit(sysfs_module_exit);
