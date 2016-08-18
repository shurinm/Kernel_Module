#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define SIZE 64

int main ()
{
    char accepted_msg[SIZE];              // принятое сообщение
    char send_msg[] = "Hello world!";   // переданное сообщение
    int fd;                             // файловый дескриптор

    fd = open("/proc/proc_file_name", O_RDWR); 
    if (fd < 0){
        perror("open /proc/proc_file_name");
        return -1;
    }

    // Считываем сообщение из пространства ядра
    if (read(fd, accepted_msg, SIZE) == -1){
        printf("ERROR: read from /proc/proc_file_name");
        return -1;
    }
    printf("Message from the kernel: %s\n", accepted_msg);

    // Спускаем сообщение в пространство ядра
    if (write(fd, send_msg, strlen(send_msg) + 1) == -1){
        printf("ERROR: write to /proc/proc_file_name");
        return -1;
    }
    close(fd);
    return 0;
}


