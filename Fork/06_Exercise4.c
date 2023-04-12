// 4
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1, pid2, pid3, pid4, pid5, pid6, pid7;

    pid1 = getpid(); // get PID of parent process
    printf("P1: PID=%d, PPID=%d\n", pid1, getppid());

    // create P2, P3, and P4 processes
    pid2 = fork();
    if (pid2 == 0)
    { // child process
        printf("P2: PID=%d, PPID=%d\n", getpid(), getppid());
        pid3 = fork();
        if (pid3 == 0)
        { // child process
            printf("P3: PID=%d, PPID=%d\n", getpid(), getppid());
            pid4 = fork();
            if (pid4 == 0)
            { // child process
                printf("P4: PID=%d, PPID=%d\n", getpid(), getppid());
                sleep(10); // simulate P4 as an orphan process
                printf("P4: I'm an orphan now!\n");
            }
            else
            {               // parent process (P3)
                wait(NULL); // wait for P4 to finish
                printf("P3: Done.\n");
            }
        }
        else
        {               // parent process (P2)
            wait(NULL); // wait for P3 to finish
            printf("P2: Done.\n");
        }
    }
    else
    { // parent process (P1)
        // create P5, P6, and P7 processes
        pid5 = fork();
        if (pid5 == 0)
        { // child process
            printf("P5: PID=%d, PPID=%d\n", getpid(), getppid());
            pid6 = fork();
            if (pid6 == 0)
            { // child process
                printf("P6: PID=%d, PPID=%d\n", getpid(), getppid());
                exit(0); // P6 finishes immediately
            }
            else
            {               // parent process (P5)
                wait(NULL); // wait for P6 to finish
                pid7 = fork();
                if (pid7 == 0)
                { // child process
                    printf("P7: PID=%d, PPID=%d\n", getpid(), getppid());
                    // simulate P7 as a zombie
                    printf("P7: I'm a zombie now!\n");
                    exit(0);
                }
                else
                {              // parent process (P5)
                    sleep(20); // simulate delay before exiting
                    printf("P5: Done.\n");
                }
            }
        }
        else
        {               // parent process (P1)
            wait(NULL); // wait for P2 to finish
            wait(NULL); // wait for P5 to finish
            printf("P1: Done.\n");
        }
    }

    return 0;
}

/* 
// 4
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1, pid2, pid3, pid4, pid5, pid6, pid7;

    pid1 = getpid(); // get PID of parent process
    printf("P1: PID=%d, PPID=%d\n", pid1, getppid());

    // create P2, P3, and P4 processes
    pid2 = fork();
    if (pid2 == 0)
    { // child process
        printf("P2: PID=%d, PPID=%d\n", getpid(), getppid());
        pid3 = fork();
        if (pid3 == 0)
        { // child process
            printf("P3: PID=%d, PPID=%d\n", getpid(), getppid());
            pid4 = fork();
            if (pid4 == 0)
            { // child process
                printf("P4: PID=%d, PPID=%d\n", getpid(), getppid());
                sleep(10); // simulate P4 as an orphan process
                printf("P4: I'm an orphan now!\n");
            }
            else
            {               // parent process (P3)
                wait(NULL); // wait for P4 to finish
                printf("P3: Done.\n");
            }
        }
        else
        {               // parent process (P2)
            wait(NULL); // wait for P3 to finish
            printf("P2: Done.\n");
        }
    }
    else
    { // parent process (P1)
        // create P5, P6, and P7 processes
        pid5 = fork();
        if (pid5 == 0)
        { // child process
            printf("P5: PID=%d, PPID=%d\n", getpid(), getppid());
            pid6 = fork();
            if (pid6 == 0)
            { // child process
                printf("P6: PID=%d, PPID=%d\n", getpid(), getppid());
                exit(0); // P6 finishes immediately
            }
            else
            {               // parent process (P5)
                wait(NULL); // wait for P6 to finish
                pid7 = fork();
                if (pid7 == 0)
                { // child process
                    printf("P7: PID=%d, PPID=%d\n", getpid(), getppid());
                    // simulate P7 as a zombie
                    printf("P7: I'm a zombie now!\n");
                    exit(0);
                }
                else
                {              // parent process (P5)
                    sleep(20); // simulate delay before exiting
                    printf("P5: Done.\n");
                }
            }
        }
        else
        {               // parent process (P1)
            wait(NULL); // wait for P2 to finish
            wait(NULL); // wait for P5 to finish
            printf("P1: Done.\n");
        }
    }

    return 0;
} 
*/