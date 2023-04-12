//1
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    int n; 
    printf("Enter no. of fork calls: ");
    scanf("%d", &n);

    int count = 0;

    for (int i = 0; i < n; ++i) {
        pid = fork();

        if (pid < 0) {
            printf("Fork failed.\n");
            return 1;
        } else if (pid == 0) {
            // child process
            printf("Child %d with parent %d.\n", getpid(), getppid());
        } else {
            // parent process
            count++;
        }
    }

    printf("Total number of child processes created: %d\n", (1 << n) - 1);

    return 0;
}
/* 
//1
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int n = 3;  // number of fork calls to make
    pid_t pid;
    int i, count = 0;

    for (i = 0; i < n; i++) {
        pid = fork();

        if (pid < 0) {
            printf("Fork failed.\n");
            return 1;
        } else if (pid == 0) {
            // child process
            printf("Child %d with parent %d.\n", getpid(), getppid());
        } else {
            // parent process
            count++;
            wait(NULL);
        }
    }

    // print total number of child processes created
    printf("Total number of child processes created: %d\n", (1 << n) - 1);

    return 0;
} 
*/