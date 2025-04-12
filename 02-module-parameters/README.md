# Linux Kernel Module - Parameters

We will get a string and an integer value from the user as module parameters.

## Usage Steps
```bash
make
sudo insmod param_module.ko username="Kemal" repeat_count=3
sudo mesg | tail -n 10
sudo rmmod param_module
```