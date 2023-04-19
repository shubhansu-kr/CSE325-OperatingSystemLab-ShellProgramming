// Problem: Inconsistent result

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// shared resource
int totalBooks = 5;

// Use lock 
pthread_mutex_t l1;

sem_t s;

// int sem_init(sem_t *sem, int pshared, unsigned int value)
// sem_init(&sem, 0, 1): We can initialise the value of semaphore s.

void* returnBook(){


    // wait
    sem_wait(&s);

    // Critical section starts 
    int local = totalBooks;
    local += 1;

    // Now to simulate preemption, we will use sleep
    sleep(5);

    totalBooks = local;
    // Critical section ends.

    // Signal
    sem_post(&s);

    printf("R totalBooks: %d\n", totalBooks);
    pthread_exit(NULL);
}

void* borrowBook(){
    
    sem_wait(&s);

    // Critical section starts.
    int local = totalBooks;

    if (local > 0) {
        local -= 1;
    }
    else {
        // No books to borrow
    }

    totalBooks = local;
    // Critical section ends.

    // Release Lock
    sem_post(&s);

    printf("B totalBooks: %d\n", totalBooks);
    pthread_exit(NULL);
}

int main() {

    printf("totalBooks: %d\n", totalBooks);

    pthread_t thread1, thread2;
    sem_init(&s, 0, 1);


    pthread_create(&thread1, NULL, returnBook, NULL);
    pthread_create(&thread2, NULL, borrowBook, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("totalBooks: %d\n", totalBooks);

    return 0;
}
