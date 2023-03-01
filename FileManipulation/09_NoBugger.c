// Exp3 Lab Exercise Q3

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{

    int fd = open("Sample.txt", O_RDONLY);
    int fileSize = lseek(fd, 0, SEEK_END);

    printf("%d\n", sizeof(char));
    char *buffer = (char *)malloc((fileSize + 1) * sizeof(char));

    lseek(fd, 0, SEEK_SET);
    int rd = read(fd, buffer, fileSize);
    buffer[rd] = '\0';

    for (int i = 0; buffer[i] != '\0'; ++i)
    {
        printf("%c", buffer[i]);
    }

    return 0;
}
