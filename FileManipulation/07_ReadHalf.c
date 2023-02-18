// Exercise: Q1: Write a program using system calls to copy half the content of the file to a newly created 
// file. first half and second half;

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main () {
    
    int fd;

    fd = open("Sample.txt", O_RDONLY);
    printf("%d\n", fd);

    int fileSize = lseek(fd, 0, SEEK_END);
    int halfSize = fileSize/2;
    printf("%d\n", fileSize);
    printf("%d\n", halfSize);

    // Create buffer to store. 
    char *buffer1 = (char *)malloc((halfSize + 1) * sizeof(char));
    char *buffer2 = (char *)malloc((halfSize + 1) * sizeof(char));

    // read half of the file.
    lseek(fd, 0, 0); 
    int rd1 = read(fd, buffer1, halfSize);
    lseek(fd, 0, halfSize);
    int rd2 = read(fd, buffer2, halfSize);

    printf("%d %d\n", rd1, rd2);

    buffer1[rd1] = '\0';
    buffer2[rd2] = '\0';
    
    int newFd1 = open("Sample1.txt", O_CREAT | O_WRONLY, 0777);
    int newFd2 = open("Sample2.txt", O_CREAT | O_WRONLY, 0777);

    int wr1 = write(newFd1, buffer1, rd1);
    int wr2 = write(newFd2, buffer2, rd2);

    return 0 ;
}
