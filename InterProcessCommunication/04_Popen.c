#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {

    FILE *fd;

    char buffer[100];
    sprintf(buffer, "name first");

    // wc is the name of process, -c is count of chars. -w will be count of words.
    fd = popen("wc -c", "w");

    fwrite(buffer, sizeof(char), strlen(buffer), fd);

    pclose(fd);

    // read

    fd = popen("ls", "r");

    fread(buffer, sizeof(char), 20, fd);

    write(1, buffer, 20);
    printf("\n");

    pclose(fd);

    return 0;
}