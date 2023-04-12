#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1, pid2;

    // create process P1
    pid1 = fork();

    if (pid1 < 0)
    {
        printf("Failed to create process P1.\n");
        return 1;
    }
    else if (pid1 == 0)
    {
        // P2 process
        printf("P2 process created with pid: %d, parent pid: %d\n", getpid(), getppid());
        pid2 = fork();

        if (pid2 < 0)
        {
            printf("Failed to create process P2.\n");
            return 1;
        }
        else if (pid2 == 0)
        {
            // P3 process
            printf("P3 process created with pid: %d, parent pid: %d\n", getpid(), getppid());
            return 0;
        }
    }
    else
    {
        // P1 process
        printf("P1 process created with pid: %d\n", getpid());
    }

    return 0;
}
/* 
//2
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    // create process P1
    pid1 = fork();

    if (pid1 < 0) {
        printf("Failed to create process P1.\n");
        exit(1);
    } else if (pid1 == 0) {
        // P2 process
        printf("P2 process created with pid: %d, parent pid: %d\n", getpid(), getppid());
        pid2 = fork();

        if (pid2 < 0) {
            printf("Failed to create process P2.\n");
            exit(1);
        } else if (pid2 == 0) {
            // P3 process
            printf("P3 process created with pid: %d, parent pid: %d\n", getpid(), getppid());
            exit(0);
        }
    } else {
        // P1 process
        printf("P1 process created with pid: %d\n", getpid());
        wait(NULL);
    }

    return 0;
} */