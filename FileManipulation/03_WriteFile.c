// Read From file 

#include <stdio.h>
#include <unistd.h> // Include header for file reading
#include <fcntl.h>

int main () {
    int fd;
    char buffer[12] = "hell";
    
    // open file in read and write mode.
    fd = open("Dummy.txt", O_RDWR | O_CREAT);
    printf("%d\n", fd);

    // handle error.
    if (fd < 0)
    {
        // Prompt error: 
        perror("open/create");
        return 1;
    }
    
    int ch = write(fd, buffer, 4);

    if (ch != 4){
        perror("Read");
        printf("Error writing the file");
        return 1;
    }

    close(fd);

    return 0 ;
}
