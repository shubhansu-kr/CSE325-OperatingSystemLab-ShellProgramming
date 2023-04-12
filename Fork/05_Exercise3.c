//3
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid1, pid2, pid3, pid4, pid5;

    // create process p1
    pid1 = getpid();
    printf("Process p1 (pid %d) is created.\n", pid1);

    // create process p2 as child of p1
    pid2 = fork();
    if (pid2 < 0) {
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (pid2 == 0) {
        // child process (p2)
        printf("Process p2 (pid %d) is created as child of p1 (pid %d).\n", getpid(), pid1);

        // create process p3 as child of p2
        pid3 = fork();
        if (pid3 < 0) {
            fprintf(stderr, "Fork failed.\n");
            return 1;
        } else if (pid3 == 0) {
            // child process (p3)
            printf("Process p3 (pid %d) is created as child of p2 (pid %d).\n", getpid(), pid2);
        } else {
            // parent process (p2)
            wait(NULL);
            printf("Process p3 (pid %d) has terminated.\n", pid3);
        }
    } else {
        // parent process (p1)
        wait(NULL);
        printf("Process p2 (pid %d) has terminated.\n", pid2);

        // create process p4 as child of p1
        pid4 = fork();
        if (pid4 < 0) {
            fprintf(stderr, "Fork failed.\n");
            return 1;
        } else if (pid4 == 0) {
            // child process (p4)
            printf("Process p4 (pid %d) is created as child of p1 (pid %d).\n", getpid(), pid1);

            // simulate an orphan process
            sleep(5);
            printf("Process p4 (pid %d) has become an orphan.\n", getpid());

            // create process p5 as child of p4
            pid5 = fork();
            if (pid5 < 0) {
                fprintf(stderr, "Fork failed.\n");
                return 1;
            } else if (pid5 == 0) {
                // child process (p5)
                printf("Process p5 (pid %d) is created as child of p4 (pid %d).\n", getpid(), pid4);
                exit(0);
            } else {
                // parent process (p4)
                sleep(10);
                printf("Process p5 (pid %d) has become a zombie.\n", pid5);
            }
        } else {
            // parent process (p1)
            wait(NULL);
            printf("Process p4 (pid %d) has terminated.\n", pid4);
        }
    }

    return 0;
}