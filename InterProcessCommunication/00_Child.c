#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int fd[2], valid2;

    pid_t chileProcess;

    char inputBuffer[] = " Welcome to LPU\n";

    char readingBuffer[50];

    // Create Pipe:
    // Signature: int pipe(int fd[2]);
    /* Returns: 0 if OK, −1 on error */
    int valid = pipe(fd);

    if (valid == -1)
    {
        printf("\nError Creating Pipe\n");
        return 0;
    }

    // The pipe function returns two file descriptors through the fd argument. The fd[0] is a file
    // descriptor that a process can use to read the data from the pipe, and fd[1] is a different file
    // descriptor that a process in use to write data to the pipe.

    if ((chileProcess = fork()) == -1)
    {
        printf("Parent failed to create the child process");
        exit(1);
    }


    if (chileProcess == 0)
    {
        // Child Created Sucessfully
        // Block executed in parent process.

        // Child has two fd
        // 1. Read the pipe(fd[0])
        // 2. Write the pipe(fd[1])

        // Child closes the read file descriptor.
        close(fd[0]);

        // Child writes in the pipe.
        write(fd[1], inputBuffer, (strlen(inputBuffer) + 1));


        printf("The information written in the pipe by child is: %s", inputBuffer);
        exit(0);
    }
    else
    {
        // Parent has two fd
        // 1. Read the pipe(fd[0])
        // 2. Write the pipe(fd[1])

        // Parent Closes write file descriptor.
        close(fd[1]);

        valid2 = read(fd[0], readingBuffer, sizeof(readingBuffer));

        printf("The information received by the parent process from the pipe is:%s", readingBuffer);
    }

    return (0);
}