#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    
    DIR* dp;
    dp = opendir("./Dir");

    struct dirent *dirPointer;

    // int retValue = mkdir("newDir", S_IRWXU | S_IRWXG);
    int fd;
    char buffer[1000];

    while(dirPointer = readdir(dp)) {
        char sourcePath[100] = "./Dir/";
        char destinationPath[100] = "./newDir/";

        char fileName[100] = "";
        strcat(fileName, dirPointer->d_name);

        strcat(sourcePath, fileName);
        strcat(destinationPath, fileName);

        fd = open(sourcePath, O_RDONLY);

        int fileLength = lseek(fd, 0, SEEK_END);
        lseek(fd, 0, 0);

        read(fd, buffer, fileLength);

        close(fd);

        fd = open(destinationPath, O_CREAT | O_RDWR, 0777);
        write(fd, buffer, fileLength);
        close(fd);

        printf("%s\n", dirPointer->d_name);
        printf("%s\n", dirPointer->d_ino);
        printf("\n");
    }

    // close(dp);
    dp = opendir("./newDir");

    printf("\n");
    while(dirPointer = readdir(dp)) {
        printf("%d: %s\n", dirPointer->d_ino, dirPointer->d_name);
    }
    printf("\n");

}