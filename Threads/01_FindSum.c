#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *findSum(void *args) {
    int *arr = (int *)args;
    int size = *(arr);

    // arr++;

    static int sum = 0;
    for (int i = 1; i < size; ++i)
    {
        sum += *(arr+i);
    }
    
    printf("Sum of Arr is: ", sum);

    return (void *)&sum;
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
    }
    
    pthread_t thread;

    int sum = pthread_create(&thread, NULL, findSum, (void *)arr);
    pthread_join(thread, NULL);

    printf("sum is %d", sum);

}