//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char ch;
    int counter = 0;
    char buffer[1];
    int fd = open("Sample.txt", O_WRONLY | O_APPEND);

    printf("Enter $ to exit \n");
    do
    {   
        scanf("%c", &ch);
        buffer[0] = ch;
        write(fd, buffer, 1);
    } while (ch != '$');
    
    return 0;
}

// int main()
// {

//     int maxSize;
//     printf("Enter the max Size of buffer: ");
//     scanf("%d", &maxSize);

//     char *buffer = (char *)malloc((maxSize + 1) * sizeof(char));

//     char ch;
//     int counter = 0;

//     printf("Enter $ to exit \n");
//     do
//     {   
//         printf("Enter char: ");
//         scanf("%c", &ch);
//         buffer[counter++] = ch;
//     } while (ch != '$');

//     buffer[counter] = '\0';

//     int fd = open("Sample.txt", O_WRONLY);
//     write(fd, buffer, counter);


//     for (int i = 0; i < buffer[i] != '\0'; ++i)
//     {
//         printf("%c", buffer[i]);
//     }
    
//     return 0;
// }
