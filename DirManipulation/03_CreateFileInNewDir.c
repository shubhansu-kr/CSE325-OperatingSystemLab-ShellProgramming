//  Ls - Abstract 

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int main (int argc, char *argv[]) {
    
    if (argc > 1) {
        mkdir(argv[1], 0777);
    }
    else {
        return 0;
    }

    char newFileName[100] = "./";
    strcat(newFileName, argv[1]);
    strcat(newFileName, "/file1.txt");
    
    int fd = open(newFileName, O_CREAT, 0777);    

    DIR *dp;

    struct dirent *direntPt;

    if (argc > 1) {
        dp = opendir(argv[1]);
    }
    else {
        dp = opendir(".");
    }

    if (dp == NULL) {
        printf("Dir %s does not exist", argv[1]);
        return 0;
    }
    

    while(direntPt = readdir(dp)) {
        printf("\n %d:", direntPt->d_ino);
        printf(" %s", direntPt->d_name); // display the name of the direct
    }

    return 0 ;
}
