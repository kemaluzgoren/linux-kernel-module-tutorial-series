# Linux Kernel Module - Sysfs

To exchange data between the kernel and the user via the /sys file system.

## Usage Steps
```bash
make
sudo insmod sysfs_module.ko
```
## Read
```bash
cat /sys/kernel/my_sysfs/myvalue
```
## Write
```bash
echo "Hello from user!" > /sys/kernel/my_sysfs/myvalue
```
## Read it again
```bash
cat /sys/kernel/my_sysfs/myvalue
```
## Clean
```bash
sudo rmmod sysfs_module
```