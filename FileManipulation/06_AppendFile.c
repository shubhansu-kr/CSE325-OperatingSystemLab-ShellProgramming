// Append data to file

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main () {
    
    int n, m;

    char buffer[100];


    // write(fd, char[], len): Writes len bytes into fd file from char array. 
    // return Number of bytes written on success
    // return 0 on reaching end of file
    // return -1 on error
    // return -1 on signal interrupt
    n = write(1, "HelloWorld", 10);

    printf("\nNo. of chars written : %d", n);


    // read(fd, char[], len): reads len bytes from fd and store into char array 
    // return Number of bytes read on success
    // return 0 on reaching end of file
    // return -1 on error
    // return -1 on signal interrupt

    int readFromConsole, writeIntoFile;

    writeIntoFile = open("Sample.txt", O_WRONLY | O_APPEND);
    
    // printf("Enter Text: ");

    // readFromConsole stores the length of user input
    readFromConsole = read(0, buffer, 21);


    // append into file with lenght of user input.
    write(writeIntoFile, buffer, readFromConsole);

    return 0 ;
}
