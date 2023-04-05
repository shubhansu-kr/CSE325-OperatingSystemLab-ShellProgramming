

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {

    pid_t pId;
    int status;

    pId = fork();  // Create a child process.

    status = getpid(); // Initialise status with pid of child

    if (pId == -1) {
        // Failed to create a child process.
        printf("Failed to create a child\n");
    }
    else if (pId == 0) {
        // Sucessfully created a child process.
        printf("Child Process is running. \n");
        sleep(2);
        printf("Child process exiting. \n");
    }
    else {
        // Parent Process.
        printf("Parent process waiting for child process to complete...\n");
        wait(&status); // waits for child to execute first.
        printf("Completing parent process.");
    }

    return 0 ;
}

