#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main ()
{
    char accepted_msg[32];              // принятое сообщение
    char send_msg[] = "Hello world!";   // переданное сообщение
    int fd;                             // файловый дескриптор

    fd = open("/dev/my_device", O_RDWR); 
    if (fd < 0){
        perror("open /dev/my_device");
        return -1;
    }

    // Считываем сообщение из пространства ядра
    if (read(fd, accepted_msg, 32) == -1){
        printf("ERROR: read from /dev/my_device");
        return -1;
    }
    printf("Message from the kernel: %s\n", accepted_msg);

    // Спускаем сообщение в пространство ядра
    if (write(fd, send_msg, strlen(send_msg) + 1) == -1){
        printf("ERROR: write to /dev/my_device");
        return -1;
    }
    close(fd);
    return 0;
}


