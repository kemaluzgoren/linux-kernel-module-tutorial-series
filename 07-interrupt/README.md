# Linux Kernel Module - interrupt

We will show you how to manage, capture and handle interrupt (IRQ) on Linux Kernel.

## Usage Steps for ioctl_module
```bash
make
sudo insmod interrupt_module.ko
sudo dmesg | tail -n 10
```
## IRQ Trigger Simulation
```bash
echo 1 | sudo tee /proc/irq/11/smp_affinity
```
## Clean
```bash
sudo rmmod interrupt_module
```
