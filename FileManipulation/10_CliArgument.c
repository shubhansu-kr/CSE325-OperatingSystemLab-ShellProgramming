// Command line argument. 

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

int main (int argc, char *argv[]) {
    
    int fd;
    fd = open(argv[1], O_RDONLY);
    
    int fileSize = lseek(fd, 0, SEEK_END);
    printf("Size of file %s is: %d", argv[1], fileSize);

    // argc - argument count 
    // argv - command line arguments. 

    // argv[0] = "./a.out" 
    // argv[i] = input from command line. 

    printf("\n %s, %d", argv[0], argc); // ./a.out 2 
    // prints argc as 2 because we are passing only 2 command line args.
    
    
    return 0 ;
}
