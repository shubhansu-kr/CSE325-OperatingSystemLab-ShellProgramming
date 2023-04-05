// Process Management

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void createChild() {
    // Fork() system call is mechanism in unix based os that 
    // allows to create a process to create a new child 
    // The new process is an exact copy of parent process, including the 
    // program code, data, and stack. 
    // The only difference between the two processes is their process ids.

    pid_t pId = getpid();
    printf("Current process PID is %d\n", pId);

    printf("Forking a child process. \n");
    pid_t childPId = fork();

    if (childPId == -1) {
        printf("Failed to fork a child process. \n");
    }
    else if (childPId == 0) {
        printf("Child process PID: %d, Parent proccess PID: %d\n", getpid(), getppid());
    }
    else {
        printf("Parent process pId: %d\n", getpid());
    }
}

int main () {
    
    
    return 0;
}