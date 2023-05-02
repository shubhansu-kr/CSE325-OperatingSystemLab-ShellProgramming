// FiFo works in blocked mode. Sender and reciever both should 
// be present 

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Sender
int main () {

    // Create a named pipe 
    int res = mkfifo("FIFO1", 0777);
    printf("Created\n");

    // Create sender program
    int fd = open("FIFO1", O_RDWR);
    write(fd, "Hell", 5);

    // Reader 
    fd = open("FIFO1", O_RDONLY);
    read(fd, buffer, 5);


    return 0;
}