// Remove Directory

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
    
    int retValue;
    retValue = rmdir(argv[1]);

    printf("RetValue is: %d", retValue);
    // 0 : Successfull removal : Only removes empty dir.
    // -1: Some error while removing dir: 

    

    return 0 ;
}
