#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int retValue;
    retValue = mkdir(argv[1], S_IRWXU | S_IRWXG);
    
    printf("Value of retValue: \n", retValue);
    
    return 0;
}