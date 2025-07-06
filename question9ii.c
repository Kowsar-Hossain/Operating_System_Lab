
Write a C program to show how two unrelated processes can communicate
with each other by a named pipe.

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {
    mkfifo("mypipe", 0666);
    int fd = open("mypipe", O_WRONLY);
    char msg[] = "Hello from writer!";
    write(fd, msg, strlen(msg)+1);
    close(fd);
    return 0;
}




#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char buffer[100];
    int fd = open("mypipe", O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    printf("Reader received: %s\n", buffer);
    close(fd);
    return 0;
}

