// Experiments 3: File Manipulation.

// Commands to compile and execute.
// > gcc fileName.c
// > ./a.out

// Write your code in a .c extention file.
// Compile the file using gcc compiler and create an executable file(a.out)
// Run the executable file(a.out).

// .sh was interpreted line by line
// .c is compiled altogether and an executable is created.

#include <stdio.h>
#include <unistd.h> // Include header for file reading
#include <fcntl.h>

void practice()
{
    printf("Hello World");
}

void openFile()
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

    if (fd < 0)
    {
        perror("Error Opening the file");
        return;
    }

    printf("Opened file with descriptor: ");
    printf("%d\n", fd); // 3 : Default value of first fd availabe.'

    // read from stdin into buffer for 10 units
    read(0, buffer, 10);

    // write from buffer into console starting from 1 index and length 10;
    write(1, buffer, 10);

    // Close(fd) : Used to close the descriptor.  Returns 0 on success and -1 on error.
    if (close(fd) == -1)
    {
        perror("Error Closing the file");
        return;
    }
}

void readFile()
{

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
}

void createWrite()
{

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

    if (ch != 4)
    {
        perror("Read");
        printf("Error writing the file");
        return 1;
    }

    close(fd);
}

int main()
{

    practice();

    return 0;
}