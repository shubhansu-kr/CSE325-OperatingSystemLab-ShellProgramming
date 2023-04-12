#include <stdio.h>
#include <pthread.h>

void *findFactorial(void *arg)
{
    int *x = (int *)arg;
    int fac = 1;
    for (int i = 1; i < *x; ++i)
    {
        fac *= i;
    }
    printf("\nFactorial of %d is %d", *x, fac);
    return NULL;
}

void *findEvenOdd(void *arg)
{
    int *x = (int *)arg;
    if ((*x) % 2)
    {
        printf("\nNumber is Odd");
    }
    else
    {
        printf("\nNumber is Even");
    }
    return NULL;
}

void* createThread()
{
    pthread_t thread1, thread2;

    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    pthread_create(&thread1, NULL, findFactorial, (void *)&n);
    pthread_create(&thread2, NULL, findEvenOdd, (void *)&n);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return NULL;
}

int main()
{
    createThread();

    return 0;
}