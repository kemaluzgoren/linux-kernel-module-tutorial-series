#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>

#define MY_IRQ_NUM 11

static irqreturn_t my_irq_handler(int irq, void *dev_id)
{
    printk(KERN_INFO "[interrupt_module] Interrupt received! IRQ: %d\n", irq);
    return IRQ_HANDLED;
}

static int __init interrupt_module_init(void)
{
    int result;

    result = request_irq(MY_IRQ_NUM, my_irq_handler, IRQF_SHARED, "my_interrupt", (void *)(my_irq_handler));
    
    if(result) {
        printk(KERN_ERR "[interrupt_module] Cannot register IRQ %d\n", MY_IRQ_NUM);
        return result;
    }

    printk(KERN_INFO "[interrupt_module] IRQ %d registered successfully\n", MY_IRQ_NUM);
    return 0;
}

static void __exit interrupt_module_exit(void)
{
    free_irq(MY_IRQ_NUM, (void *)(my_irq_handler));
    printk(KERN_INFO "[interrupt_module] IRQ %d freed\n", MY_IRQ_NUM);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kemal");
MODULE_DESCRIPTION("Linux Kernel Interrupt Example");

module_init(interrupt_module_init);
module_exit(interrupt_module_exit);
