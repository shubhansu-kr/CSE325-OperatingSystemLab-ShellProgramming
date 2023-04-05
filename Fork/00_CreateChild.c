// Process Management: Create child using fork

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// Fork() system call is mechanism in unix based os that
// allows to create a process to create a new child
// The new process is an exact copy of parent process, including the
// program code, data, and stack.
// The only difference between the two processes is their process ids.

int main()
{

    pid_t pId = getpid();
    printf("Current process PID is %d\n", pId);

    printf("Forking a child process. \n");
    int counter = 1;
    pid_t childPId = fork();

    
    if (childPId == -1)
    {
        printf("Failed to fork a child process. \n");
    }
    else if (childPId == 0)
    {
        printf("\nchildPID : %d\n", childPId);
        printf("COunter : %d \n", counter++);
        printf("Child process PID: %d, Parent proccess PID: %d\n", getpid(), getppid());
    }
    else
    {
        printf("\nchildPID : %d\n", childPId);
        printf("COunter : %d \n", counter++);
        printf("Parent process pId: %d\n", getpid());
    }

    // Output

    // Current process PID is 123
    // Forking a child process.

    // childPID : 124
    // COunter : 0
    // Parent process pId: 123
    // Counter after update : 1

    // childPID : 0
    // COunter : 0
    // Child process PID: 124, Parent proccess PID: 8
    // Counter after update : 1

    // Explanation: 
    // When parent process is being executed, fork returned the pid of child 
    // so the program enters in the else block. 
    // When the child process is being executed, childPid is set to 0 so else if block
    // is executed. 

    // Now the counter variable is copied in the child process instead of passing reference
    // So, the counter is not updated.

    return 0;
}