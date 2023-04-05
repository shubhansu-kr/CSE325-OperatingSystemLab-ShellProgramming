// Process Management: Create child using fork

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// The fork system call is a mechanism in unix based operating system that allows 
// to create a new child process. The new process is an exact copy of the parent process
// including the program code, data and stack. The only difference between the two 
// process is their process id. 

// When a program calls fork(), the operating system creates a new process by duplicationg the calling 
// process. This new process is caclled the child process, and it runs the same code as parent process.
// The child process has its own copy of the parent's address space, which means 
// that any changes made to th memory by the child processs will not affect the prarent process.

// The fork system call returns differnt values to th parent and child processes. thee the parent process, 
// fork returns the pid of hte child process, while 
// in the child process, it returns zero. 
// this allows the parent and child processes to differentiate between each other and take 
// different actions based on their 
// respective pids. 

// After the child process is created, both the parent and child 

int main()
{

    pid_t pId = getpid();
    printf("Current process PID is %d\n", pId);

    printf("\nHello\n"); // prints only once if we provide '\n'
                         // prints 4 times without '\n' in print statement. 

    pid_t childPid = fork();
    pid_t childPid1 = fork();

    printf("Hello\n"); // executes 4 time (1 parent + 3 child);


    return 0;
}