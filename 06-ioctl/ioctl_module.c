#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/ioctl.h>

#define DEVICE_NAME "ioctl_device"
#define CLASS_NAME "ioctl_class"

#define IOCTL_GET_MSG _IOR('k', 1, char *)
#define IOCTL_CLR_MSG _IO('k', 2)

static int major;
static char kernel_buffer[100] = "Initial Message";
static struct class* ioctl_class = NULL;
static struct device* ioctl_device = NULL;

static int dev_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "[ioctl_module] Device opened\n");
    return 0;
}

static int dev_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "[ioctl_module] Device closed\n");
    return 0;
}

static ssize_t dev_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset)
{
    if (len > sizeof(kernel_buffer))
        len = sizeof(kernel_buffer) - 1;

    if (copy_from_user(kernel_buffer, buffer, len))
        return -EFAULT;

    kernel_buffer[len] = '\0';
    printk(KERN_INFO "[ioctl_module] Written: %s\n", kernel_buffer);
    return len;
}

static long dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    switch(cmd) {
        case IOCTL_GET_MSG:
            if (copy_to_user((char __user *)arg, kernel_buffer, strlen(kernel_buffer) + 1))
                return -EFAULT;
            break;

        case IOCTL_CLR_MSG:
            memset(kernel_buffer, 0, sizeof(kernel_buffer));
            printk(KERN_INFO "[ioctl_module] Message cleared\n");
            break;

        default:
            return -EINVAL;
    }

    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = dev_open,
    .release = dev_release,
    .write = dev_write,
    .unlocked_ioctl = dev_ioctl,
};

static int __init ioctl_module_init(void)
{
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) return major;

    ioctl_class = class_create(CLASS_NAME);
    ioctl_device = device_create(ioctl_class, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);

    printk(KERN_INFO "[ioctl_module] Module loaded, Major: %d\n", major);
    return 0;
}

static void __exit ioctl_module_exit(void)
{
    device_destroy(ioctl_class, MKDEV(major, 0));
    class_unregister(ioctl_class);
    class_destroy(ioctl_class);
    unregister_chrdev(major, DEVICE_NAME);

    printk(KERN_INFO "[ioctl_module] Module unloaded\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kemal");
MODULE_DESCRIPTION("Char Device with ioctl example");

module_init(ioctl_module_init);
module_exit(ioctl_module_exit);
