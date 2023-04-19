// Problem: Inconsistent result

#include <stdio.h>
#include <pthread.h>

// shared resource
int totalBooks = 5;

// Use lock 
pthread_mutex_t l1;

void* returnBook(){


    // Take lock(access) on totalBooks
    pthread_mutex_lock(&l1);

    // Critical section starts 
    int local = totalBooks;
    local += 1;

    // Now to simulate preemption, we will use sleep
    sleep(5);

    totalBooks = local;
    // Critical section ends.

    // Release lock on totalBooks.
    pthread_mutex_unlock(&l1);

    printf("R totalBooks: %d\n", totalBooks);
    pthread_exit(NULL);
}

void* borrowBook(){
    
    // Accuire Lock
    pthread_mutex_lock(&l1);

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
    pthread_mutex_unlock(&l1);

    printf("B totalBooks: %d\n", totalBooks);
    pthread_exit(NULL);
}

int main() {

    printf("totalBooks: %d\n", totalBooks);

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, returnBook, NULL);
    pthread_create(&thread2, NULL, borrowBook, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("totalBooks: %d\n", totalBooks);

    return 0;
}
