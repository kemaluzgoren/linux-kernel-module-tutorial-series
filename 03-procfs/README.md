# Linux Kernel Module - Procfs

Exchange data between the user-space and the kernel-space

## Usage Steps
```bash
make
sudo insmod procfs_module.ko
```
## Read
```bash
cat /proc/myprocfile
```
## Write
```bash
echo "Hello from user!" > /proc/myprocfile
```
## Read it again
```bash
cat /proc/myprocfile
```
## Clean
```bash
sudo rmmod procfs_module
```