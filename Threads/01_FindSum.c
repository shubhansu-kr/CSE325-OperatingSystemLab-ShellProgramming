#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *findSum(void *args) {
    int *arr = (int *)args;
    int size = *(arr);

    // arr++;

    int sum = 0;
    for (int i = 1; i <= size; ++i)
    {
        sum += *(arr+i);
    }
    
    printf("Sum of Arr is: %d\n", sum);

    pthread_exit(sum);

    return NULL;
}

int main() {

    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(sizeof(int)* n+1);

    *(arr) = n;
    for (int i = 1; i <= n; ++i)
    {
        *(arr+i) = i*12;
        printf("\n %d", i*12);
    }
    
    pthread_t thread;

    // check: 0 : Successfully created thread
    int check = pthread_create(&thread, NULL, findSum, (void *)arr);

    void *sum;

    // Pass the pointer to pointer to the variable you want to store the result in. 
    pthread_join(thread, &sum);

    printf("sum is %d", sum);

}