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


void createWrite(){

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
}


int main()
{

    practice();

    return 0;
}