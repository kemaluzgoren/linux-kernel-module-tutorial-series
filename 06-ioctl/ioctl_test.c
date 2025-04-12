#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

#define DEVICE_PATH "/dev/ioctl_device"

#define IOCTL_GET_MSG _IOR('k', 1, char *)
#define IOCTL_CLR_MSG _IO('k', 2)

int main()
{
    int fd;
    char read_buf[100];

    fd = open(DEVICE_PATH, O_RDWR);
    if(fd < 0) {
        perror("Failed to open device");
        return EXIT_FAILURE;
    }

    printf("Writing to device: 'Kemal Kernel'\n");
    write(fd, "Kemal Kernel", strlen("Kemal Kernel"));

    printf("Reading using ioctl...\n");
    if(ioctl(fd, IOCTL_GET_MSG, read_buf) == -1) {
        perror("ioctl get message failed");
        close(fd);
        return EXIT_FAILURE;
    }
    printf("Data from kernel: %s\n", read_buf);

    printf("Clearing kernel buffer using ioctl...\n");
    if(ioctl(fd, IOCTL_CLR_MSG) == -1) {
        perror("ioctl clear failed");
        close(fd);
        return EXIT_FAILURE;
    }

    close(fd);
    return EXIT_SUCCESS;
}
