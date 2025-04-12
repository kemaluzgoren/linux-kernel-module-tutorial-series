#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "mychardev"
#define BUF_LEN 100

static int major;
static char msg[BUF_LEN] = {0};
static int msg_len = 0;

static int my_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "[mychardev] Device opened\n");
    return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "[mychardev] Device closed\n");
    return 0;
}

static ssize_t my_read(struct file *file, char *buffer, size_t len, loff_t *offset)
{
    int bytes = msg_len - *offset;
    if (bytes <= 0) return 0;
    if (len < bytes) bytes = len;
    
    if (copy_to_user(buffer, msg + *offset, bytes)) return -EFAULT;
    *offset += bytes;
    printk(KERN_INFO "[mychardev] Data read\n");
    return bytes;
}

static ssize_t my_write(struct file *file, const char *buffer, size_t len, loff_t *offset)
{
    if (len > BUF_LEN) len = BUF_LEN;
    if (copy_from_user(msg, buffer, len)) return -EFAULT;
    msg_len = len;
    printk(KERN_INFO "[mychardev] Data written\n");
    return len;
}

static struct file_operations fops = {
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write
};

static int __init my_init(void)
{
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        printk(KERN_ALERT "[mychardev] Register failed\n");
        return major;
    }
    printk(KERN_INFO "[mychardev] Module loaded, Major: %d\n", major);
    return 0;
}

static void __exit my_exit(void)
{
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "[mychardev] Module unloaded\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kemal");
MODULE_DESCRIPTION("Simple Char Device Example");

module_init(my_init);
module_exit(my_exit);