#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/shm.h>

// Writer Program
int main() {
    
    void *sharedMem;

    char buffer[100];

    int shmId;

    shmId = shmget((key_t)121, 2048, 0666 | IPC_CREAT);
    sharedMem = shmat(shmId, NULL, 0);

    read(0, buffer, 21);
    strcpy(sharedMem, buffer);

    return 0;
}

// Reader Program
int main() {

    void *sharedMem;

    char buffer[100];

    int shmId;

    shmId = shmget((key_t)121, 2048, 0666);
    sharedMem = shmat(shmId, NULL, 0);

    printf("Read data is : %s", (char *)sharedMem);

    return 0;
}