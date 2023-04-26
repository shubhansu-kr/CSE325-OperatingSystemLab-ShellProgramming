#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int fd[2], nb;

    pid_t cpid;

    char inf[] = " Welcome to LPU\n";

    char rbuff[50];

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

    if ((cpid = fork()) == -1)
    {
        printf(" Parent failed to create the child process");
        exit(1);
    }


    if (cpid == 0)
    {
        // Child Created Sucessfully
        // Block executed in parent process.

        // Parent has two fd
        // 1. Read the pipe(fd[0])
        // 2. Write the pipe(fd[1])

        // Parent closes the read file descriptor.
        close(fd[0]);

        // Parent writes in the pipe.
        write(fd[1], inf, (strlen(inf) + 1));


        printf("The information written in the pipe by parent is: %s", inf);
        exit(0);
    }
    else
    {
        // Child has two fd
        // 1. Read the pipe(fd[0])
        // 2. Write the pipe(fd[1])

        // Child Closes write file descriptor.
        close(fd[1]);

        nb = read(fd[0], rbuff, sizeof(rbuff));
        
        printf("The information received by the child process from the pipe is:%s", rbuff);
    }

    return (0);
}