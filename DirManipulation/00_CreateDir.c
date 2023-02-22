// Creating directory.

#include <stdio.h>

// dirent.h contains the structure for directory management.
#include <dirent.h>

// Library for mkdir
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>


// struct dirent
// {
//     Ino_t d_ino;             /* inode number */
//     off_ t d_off;            /* off_set to the next dirent */
//     unsigned short d_reclen; /* length of this record */
//     unsigned char d_type;    /* type of file; not supported by all file system types */
//     char d_name[256];        /* filename */
// };

int main()
{
    // mkdir()
    // opendir()
    // readdir()
    // rmdir()

    DIR *dp;

    // Content of dir like
    struct dirent *dptr;

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

    // Segmentation fault.
    // while (NULL != (dptr = readdir(dp)))
    // {
    //     printf("%s \n", dptr->d_name);
    //     printf("%s \n", dptr->d_type);
    // }

    return 0;
}
