#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t empty, full;

char buffer[5];
int index = 0;

void *produce(){

    // produce only in buffer is not full.
    // if empty is 0, it means, buffer is full.
    sem_wait(&empty);
    buffer[index] = (char)('A' + index);

    // increase index 
    index++;

    // increase full by 1;
    sem_post(&full);
}

void *consume(){

    // consume only if buffer is not empty;
    // if full is 0, means buffer is empty.
    sem_wait(&full);

    // decrease index;
    index--;

    printf("Consumed Data at index %d is %c\n", index, buffer[index]);


    // increase empty by 1;
    sem_post(&empty);
}


int main() {

    // Fix the size of buffer to 5 or take input from user. 
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);

    // full semaphore represents number of locations which are occupied
    // empty semaphore represents the no. of loc which are free.

    // Make as many produce and consume as you like to demonstrate producer
    // consumer problem.
    pthread_t t1, t2, t3, t4;

    // try to consume without any data. 
    pthread_create(&t1, NULL, consume, NULL);

    // produce data 
    pthread_create(&t2, NULL, produce, NULL);

    // consume data
    pthread_create(&t3, NULL, consume, NULL);

    // produce data
    pthread_create(&t4, NULL, produce, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    return 0;
}