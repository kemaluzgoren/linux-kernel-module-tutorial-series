#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define PROC_NAME "myprocfile"
#define BUFFER_SIZE 100

static char proc_data[BUFFER_SIZE] = "Initial kernel data\n";

static ssize_t proc_read(struct file *file, char __user *buffer, size_t count, loff_t *pos)
{
    return simple_read_from_buffer(buffer, count, pos, proc_data, strlen(proc_data));
}

static ssize_t proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
    if (count > BUFFER_SIZE) count = BUFFER_SIZE;
    if (copy_from_user(proc_data, buffer, count)) return -EFAULT;
    proc_data[count] = '\0';
    return count;
}

static struct proc_ops proc_fops = {
    .proc_read = proc_read,
    .proc_write = proc_write,
};

static int __init procfs_module_init(void)
{
    proc_create(PROC_NAME, 0666, NULL, &proc_fops);
    printk(KERN_INFO "[procfs_module] /proc/%s created\n", PROC_NAME);
    return 0;
}

static void __exit procfs_module_exit(void)
{
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "[procfs_module] /proc/%s removed\n", PROC_NAME);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kemal");
MODULE_DESCRIPTION("Example Kernel Module using procfs");

module_init(procfs_module_init);
module_exit(procfs_module_exit);
