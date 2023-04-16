#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *findLength(void *args){
    char *str = (char *)(args);

    int len = 0;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        ++len;
    }
    
    pthread_exit(len);
    return NULL;
}

int main() {
    char str[100];

    printf("Enter String: ");
    scanf("%s", &str);

    pthread_t thread;
    void *res;

    pthread_create(&thread, NULL, findLength, (void *)(str));
    pthread_join(thread, &res);

    printf("Length of string is : %s\n", res);
    
    return 0;
}