#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>

// writer lock
sem_t wr, rd, mutex;
int readerCount = 0;

// Make sure you have a file named (Capital S)Sample.txt in the folder your
// are running this program.

// Reads content of file-Sample.txt and displays on the console.
void *reader()
{
    // Don't read if writer is active
    sem_wait(&mutex);

    // Don't read if number of reader is exceeded.
    sem_wait(&rd);

    readerCount++;
    if (readerCount == 1)
    {
        // Even if one reader is present dont let writer enter.
        sem_wait(&wr);
    }

    printf("\n Entered Reader %d\n", readerCount);

    // Code for reading file.
    {
        int fd;
        char buffer[12];

        // open file in read only mode.
        fd = open("Sample.txt", O_RDONLY);
        printf("%d\n", fd);

        // if the file does not exist, open() will genrate error and assign -1 to fd;
        // handle error.
        if (fd < 0)
        {
            // Prompt error:
            perror("open");
            printf("File does not Exist");
            return 0;
        }

        int ch = read(fd, buffer, 11);

        if (ch != 11)
        {
            perror("Read");
            printf("Error reading the file");
            return 0;
        }

        buffer[ch] = '\0';

        for (int i = 0; buffer[i] != '\0'; ++i)
        {
            printf("%c", buffer[i]);
        }

        printf("%s", buffer);

        close(fd);
    }
    // Code for reading file ends

    printf("\n Exit reader %d\n", readerCount);

    readerCount--;
    if (readerCount == 0)
    {
        // allow writer
        sem_post(&wr);
    }

    // increase reader, increase mutex.
    sem_post(&mutex);
    sem_post(&rd);
}

// Write in file Sample.txt
void *writer()
{
    // Don't write if one writer is already there
    sem_wait(&wr);

    // Lock reader
    sem_wait(&mutex);

    printf("\n Enter writer\n");

    // Code for writing
    {
        printf("Entering writing editor....\n");

        char ch;
        int fd = open("Sample.txt", O_WRONLY | O_APPEND);

        printf("Enter $ to exit \n");
        do
        {
            scanf("%c", &ch);
            write(fd, &ch, 1);
        } while (ch != '$');
    }

    printf("\n Exit Writer\n");

    // Release reader
    sem_post(&mutex);

    // Free writer
    sem_post(&wr);
}

int main()
{

    // fix the number of reader to 5; - You can change it.
    int n = 5;

    sem_init(rd, 0, n);
    sem_init(wr, 0, 1); // only one writer allowed;
    sem_init(mutex, 0, 1);

    // Create thread,, and keep on calling reader writer according to 
    // your need or simulation

    // Template to create a thread and execute fxn
    // pthread_t t1;
    // pthread_create(&t1, NULL, reader, NULL);
    // pthread_join(t1, NULL);

    return 0;
}