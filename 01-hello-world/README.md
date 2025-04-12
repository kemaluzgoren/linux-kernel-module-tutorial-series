# Linux Kernel Module - Hello World

Simple example of a Linux Kernel Module written in C.

## Build & Run

### 1. Install Kernel Headers
```bash
sudo apt update
sudo apt install build-essential linux-headers-$(uname -r)
```
### 2.Build the Module
```bash
make
```
### 3.Insert the Module
```bash
sudo insmod hello.ko
```
Check Kernel Log: 
```bash
sudo dmesg | tail -n 10
```
### 4.Remove the Module
```bash
sudo rmmod hello
```
### Clean
```bash
make clean
```

### Notes
* Tested on Ubuntu 22.04
* Kernel Version: 6.8.0-52-generic
* GCC Version: gcc-12 recommended (or kernel compiled version)