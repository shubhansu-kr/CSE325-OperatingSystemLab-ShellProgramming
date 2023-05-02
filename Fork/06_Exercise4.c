// 4

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{

    pid_t pid2, pid5;

    pid2 = fork();

    if (pid2 < 0)
    {
        return 0;
    }
    else if (pid2 == 0)
    {
        // P2 (child P1);

        // Create Child P3
        pid_t pid3 = fork();

        if (pid3 < 0)
        {
            return 0;
        }
        else if (pid3 == 0)
        {
            // P3 (child of P2)

            pid_t pid4 = fork();

            if (pid4 < 0)
            {
                return 0;
            }
            else if (pid4 == 0)
            {
                // P4 (child of P3)

                // P4 as orphan process 
                // Put child to sleep;

                sleep(10);
            }
            else
            {
                // P3 Execution
            }
        }
        else
        {
            // P2 Execution
        }
    }
    else
    {
        // P1 (parent process)

        pid5 = fork();
        if (pid5 < 0)
        {
            return 0;
        }
        else if (pid5 == 0)
        {
            // P5 (child P1)

            // Create Child P6
            pid_t pid6 = fork();

            if (pid6 < 0)
            {
                return 0;
            }
            else if (pid6 == 0)
            {
                // P6 (child of P5)

                pid_t pid7 = fork();

                if (pid7 < 0)
                {
                    return 0;
                }
                else if (pid7 == 0)
                {
                    // P7 (child of P6)
    
                    // P7 as zombie. 
                    // Put parent(P6) to sleep.
                }
                else
                {
                    // P6 Execution
                    sleep(10);
                }
            }
            else
            {
                // P5 Execution
            }
        }
        else
        {
            // P1 
        }
    }

    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>

// int main()
// {
//     pid_t pid2, pid5, pid3, pid4, pid5, pid6, pid7;

//     pid2 = getpid(); // get PID of parent process
//     printf("P1: PID=%d, PPID=%d\n", pid2, getppid());

//     // create P2, P3, and P4 processes
//     pid5 = fork();
//     if (pid5 == 0)
//     { // child process
//         printf("P2: PID=%d, PPID=%d\n", getpid(), getppid());
//         pid3 = fork();
//         if (pid3 == 0)
//         { // child process
//             printf("P3: PID=%d, PPID=%d\n", getpid(), getppid());
//             pid4 = fork();
//             if (pid4 == 0)
//             { // child process
//                 printf("P4: PID=%d, PPID=%d\n", getpid(), getppid());
//                 sleep(10); // simulate P4 as an orphan process
//                 printf("P4: I'm an orphan now!\n");
//             }
//             else
//             {               // parent process (P3)
//                 wait(NULL); // wait for P4 to finish
//                 printf("P3: Done.\n");
//             }
//         }
//         else
//         {               // parent process (P2)
//             wait(NULL); // wait for P3 to finish
//             printf("P2: Done.\n");
//         }
//     }
//     else
//     { // parent process (P1)
//         // create P5, P6, and P7 processes
//         pid5 = fork();
//         if (pid5 == 0)
//         { // child process
//             printf("P5: PID=%d, PPID=%d\n", getpid(), getppid());
//             pid6 = fork();
//             if (pid6 == 0)
//             { // child process
//                 printf("P6: PID=%d, PPID=%d\n", getpid(), getppid());
//                 exit(0); // P6 finishes immediately
//             }
//             else
//             {               // parent process (P5)
//                 wait(NULL); // wait for P6 to finish
//                 pid7 = fork();
//                 if (pid7 == 0)
//                 { // child process
//                     printf("P7: PID=%d, PPID=%d\n", getpid(), getppid());
//                     // simulate P7 as a zombie
//                     printf("P7: I'm a zombie now!\n");
//                     exit(0);
//                 }
//                 else
//                 {              // parent process (P5)
//                     sleep(20); // simulate delay before exiting
//                     printf("P5: Done.\n");
//                 }
//             }
//         }
//         else
//         {               // parent process (P1)
//             wait(NULL); // wait for P2 to finish
//             wait(NULL); // wait for P5 to finish
//             printf("P1: Done.\n");
//         }
//     }

//     return 0;
// }

/*
// 4
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid2, pid5, pid3, pid4, pid5, pid6, pid7;

    pid2 = getpid(); // get PID of parent process
    printf("P1: PID=%d, PPID=%d\n", pid2, getppid());

    // create P2, P3, and P4 processes
    pid5 = fork();
    if (pid5 == 0)
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