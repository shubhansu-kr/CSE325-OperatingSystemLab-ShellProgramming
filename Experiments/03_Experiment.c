#include <stdio.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>

void createDir() {
    DIR *dp;

    // return 0: on successfull completion -1 on failure.
    int b = mkdir("dir1", 0777);

    if (b == 0) {
        printf("Dir Created Sucessfully\n");
    }
    else {
        printf("Dir Not created ");
    }

    dp = opendir("dir1");

    printf("Dir Opened Sucessfully\n");
}

int main() {  

    return 0;
}
