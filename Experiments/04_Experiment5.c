// Process Management

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void printFork2() {

    pid_t childPid = fork();
    pid_t childPid1 = fork();

    printf("printf\n"); // printed only 4 times: 1 from parent. 3 from child.

}

void printFork1() {

    printf("printf\n"); // printed only 1 times with '\n' : 1 from parent. 0 from child.

    pid_t childPid = fork();
    pid_t childPid1 = fork();
}

void printFork() {

    printf("printf"); // printed 4 times since print statement is without \n

    pid_t childPid = fork();
    pid_t childPid1 = fork();
}

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