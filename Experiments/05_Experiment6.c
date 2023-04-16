#include <stdio.h>
#include <pthread.h>

// ||||------------------------------------------------------------------------------------------------

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

    // Return the value from function.
    pthread_exit(sum);

    return NULL;
}

void *returnValueFromThread() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(sizeof(int)* n+1);

    *(arr) = n;
    for (int i = 1; i <= n; ++i)
    {
        *(arr+i) = i*12;
        printf("%d\n", i*12);
    }
    
    pthread_t thread;

    // check: 0 : Successfully created thread
    int check = pthread_create(&thread, NULL, findSum, (void *)arr);

    void *sum;

    // Pass the pointer to pointer to the variable you want to store the result in. 
    pthread_join(thread, &sum);

    printf("sum is %d", sum);
}

// |||| ---------------------------------------------------------------------------------------------------


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

    // pthread_create() returns zero when the call completes successfully. 
    // Any other return value indicates that an error occurred.

    pthread_create(&thread1, NULL, findFactorial, (void *)&n);
    pthread_create(&thread2, NULL, findEvenOdd, (void *)&n);

    // The pthread_join() function waits for a thread to terminate, detaches the thread, 
    // then returns the threads exit status. If the status parameter is NULL, the threads 
    // exit status is not returned.
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return NULL;
}

// ||||------------------------------------------------------------------------------------------------------

int main()
{
    createThread();

    return 0;
}