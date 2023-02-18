// Read From file 

#include <stdio.h>
#include <unistd.h> // Include header for file reading
#include <fcntl.h>

int main () {
    int fd;
    char buffer[12];

    // open file in read only mode.
    fd = open("Sample.txt", O_RDONLY);
    printf("%d\n", fd);

    // if the file does not exist, open() will genrate error and assign -1 to fd;
    // handle error.
    if (fd < 0)
    {
        // Prompt error:
        perror("open");
        printf("File does not Exist");
        return 0;
    }

    int ch = read(fd, buffer, 11);

    if (ch != 11)
    {
        perror("Read");
        printf("Error reading the file");
        return 0;
    }

    buffer[ch] = '\0';

    for (int i = 0; buffer[i] != '\0'; ++i)
    {
        printf("%c", buffer[i]);
    }

    printf("%s", buffer);

    close(fd);

    return 0 ;
}
