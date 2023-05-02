#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *arrMin(void *arr) {
    int *nums = (int *)arr;

    int size = *(nums);
    int min = 3244323;

    for (int i = 1; i <= size; ++i)
    {
        if (*(nums+i) < min) {
            min = *(nums+i);
        }
    }

    pthread_exit(&min);
    return NULL;
}

void *arrMax(void *arr) {
    int *nums = (int *)arr;

    int size = *(nums);
    int max = -132423;

    for (int i = 1; i <= size; ++i)
    {
        if (*(nums+i) > max) {
            max = *(nums+i);
        }
    }

    pthread_exit(&max);

    
    return NULL;
}

void *arrAvg(void *arr) {
    int *nums = (int *)arr;

    int size = *(nums);
    int sum = 0;

    for (int i = 1; i <= size; ++i)
    {
        sum += *(nums+i);
    }

    printf("sum %d \n", sum);

    pthread_exit(&sum);

    return NULL;
}

int main() {

    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    int *nums = (int *)malloc((n+1)*sizeof(int));
    *nums = n;

    printf("\n");

    for (int i = 1; i <= n; ++i)
    {
        printf("Enter %d: ", i);
        scanf("%d", nums+i);
    }

    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, arrAvg, (void *)(nums));
    pthread_create(&thread2, NULL, arrMin, (void *)(nums));
    pthread_create(&thread3, NULL, arrMax, (void *)(nums));

    void *res;

    pthread_join(thread1, &res);
    printf("arr avg = %d\n", res);

    pthread_join(thread2, &res);
    printf("arr min = %d\n", res);

    pthread_join(thread3, &res);
    printf("arr max = %d\n", res);

    return 0;
}