# Linux Kernel Module - ioctl

To exchange data between the user and the kernel via char device with special commands using ioctl().


## Usage Steps for ioctl_module
```bash
make
sudo insmod ioctl_module.ko
sudo dmesg | tail -n 10
sudo mknod /dev/ioctl_device c <major> 0
sudo chmod 666 /dev/ioctl_device
```

## Usage Steps for ioctl_test
```bash
gcc ioctl_test.c -o ioctl_test
./ioctl_test
```

Expected Output
```bash
Writing to device: 'Kemal Kernel'
Reading using ioctl...
Data from kernel: Kemal Kernel
Clearing kernel buffer using ioctl...
```
