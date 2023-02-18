// Append to file.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd;
    // fd is file descriptor: An integer which identifies the open file of the process.
    
    // There are three standard file descriptor:
    // 0 : Read from stdin
    // 1 : Write to stdout
    // 2 : Write to stderr 

    // Usually the first fd which is assigned to user is 3 because {0, 1, 2} are reserved.
    // Open functions returs a -1 when there is any error in opening file. 

    char buffer[100];
    
    // Open file in read only mode.
    fd = open("Sample.txt", O_RDONLY);

    if (fd < 0) {
        perror("Error Opening the file");
        return 1;
    }

    printf("Opened file with descriptor: ");

    printf("%d\n", fd); // 3 : Default value of first fd availabe.'



    // Seek pointer from end of file and move 10 char backwards.
    // lseek(fd, -10, SEEK_END);



    // read from stdin into buffer for 10 units 
    read(0, buffer, 10);

    // write from buffer into console starting from 1 index and length 10;
    write(1, buffer, 10);



    // Close(fd) : Used to close the descriptor.  Returns 0 on success and -1 on error.
    
    if (close(fd) == -1) {
        perror("Error Closing the file");
        return 1;
    }

    return 0 ;
}
