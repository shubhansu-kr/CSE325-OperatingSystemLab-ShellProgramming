// Process Management

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void exercise4() {
    
}

void exercise3() {

}

void exercise2() {
    // Write a program using systems for operations on processes to create a hierarchy of 
    // processes P1 → P2 → P3. Also print the id and parent id for each process.



}

void exercise1() {
    
    // Write a program using system calls for operation on process to simulate that n fork calls create (2n – 1) child processes

    int n; 
    printf("Enter no. of fork calls: ");
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        fork();
    }
    printf("print statement: Hell");
    
}

void orphanChild() {
    // If the parent process completes execution before the child process completes it's execution. 
    // The child process is called orphanChild.

    pid_t pId;
    int status; 

    pId = fork();  // Create a child process.

    if (pId == -1) {
        // Failed to create a child process. 
        printf("Failed to create a child\n");
    }
    else if (pId == 0) {
        // Sucessfully created a child process. 
        printf("Child Process is running. \n");
        status = sleep(2);
        printf("Child process exiting. \n");
    }
    else {
        // Parent Process. 
        printf("Parent process waiting for child process to complete...\n");
        wait(&status);
        printf("Completing parent process.");
    }
}

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