# Linux Kernel Module - Char Device
It provides a character-based data exchange between the user-space and the kernel-space.

## Usage Steps
```bash
make
sudo insmod mychardev.ko
sudo dmesg | tail -n 10
```
Example
```bash
[mychardev] Module loaded, Major: 240
```
## Create Device Node
```bash
sudo mknod /dev/mychardev c 240 0
sudo chmod 666 /dev/mychardev
```
## Test
```bash
echo "Hello Char Device" > /dev/mychardev
cat /dev/mychardev
```
Expected Output
```bash
Hello Char Device
```
## Clean
```bash
sudo rmmod mychardev
sudo rm /dev/mychardev
make clean
```