#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char buffer[80];
    char *named_pipe_path = "/home/sania/os/Namedpipe";

    // Open the named pipe for reading
    int fd = open(named_pipe_path, O_RDONLY);
    if (fd < 0) {
        perror("File open error");
        exit(EXIT_FAILURE);
    }

    // Read data from the pipe
    read(fd, buffer, sizeof(buffer));

    // Print the received message
    printf("Received: %s\n", buffer);

    // Close the pipe
    close(fd);

    return 0;
}
