// Write a program using pthread to concatenate the strings, where multiple strings are passed to thread function.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct strArray {
    int size;
    char **ptr;
};

void *concatinateStrings(void *args) {
    struct strArray *myArgs = (struct strArray *)args;

    int n = myArgs->size;
    char **arr = myArgs->ptr;

    char *result = (char*)malloc(100 * sizeof(char));

    for (int i = 0; i < n; ++i)
    {
        strcat(result, arr[i]);
    }


    printf("Thread: %s", result);
    pthread_exit(result);
    
    return NULL;
}

int main () {
    
    int n;
    printf("Enter the number of strings: ");
    scanf("%d", &n);

    int x = 21;

    char **ptr = (char **)malloc(n * sizeof(char *));
    printf("\n\n");

    for (int i = 0; i < n; ++i)
    {
        printf("Enter the size of string: ");
        scanf("%d", &x);

        ptr[i] = (char *)malloc((x+1) * sizeof(char));

        printf("Enter string %d: ", i);
        scanf("%s", ptr[i]);
        printf("Scanned: %s\n", ptr[i]);
    }    

    printf("\n\n");

    struct strArray *args = (struct strArray*)malloc(sizeof(struct strArray));
    args->size = n;
    args->ptr = ptr;


    pthread_t thread;
    void *res;

    pthread_create(&thread, NULL, concatinateStrings, (void *)(args));
    pthread_join(thread, &res);

    printf("\n\n");
    printf("Concatinated String is : %s", res);

    return 0;
}