//  Ls - Abstract 

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

// struct dirent
// {
//     Ino_t d_ino;             /* inode number */
//     off_ t d_off;            /* off_set to the next dirent */
//     unsigned short d_reclen; /* length of this record */
//     unsigned char d_type;    /* type of file; not supported by all file system types */
//     char d_name[256];        /* filename */
// };

int main (int argc, char *argv[]) {
    
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
