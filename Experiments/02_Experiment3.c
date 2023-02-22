// Experiments 3: File Manipulation.

// Commands to compile and execute.
// > gcc fileName.c
// > ./a.out

// Write your code in a .c extention file.
// Compile the file using gcc compiler and create an executable file(a.out)
// Run the executable file(a.out).

// .sh was interpreted line by line
// .c is compiled altogether and an executable is created.

#include <stdio.h>
#include <unistd.h> // Include header for file reading
#include <fcntl.h>

void practice()
{
    printf("Hello World");
}

void fileToConsole() {
    FILE* ptr;
	char ch;

	// Opening file in reading mode
	ptr = fopen("Sample.txt", "r");

	if (NULL == ptr) {
		printf("file can't be opened \n");
	}

	printf("content of this file are \n");

	do {
		ch = fgetc(ptr);
		printf("%c", ch);

	} while (ch != EOF);

	fclose(ptr);
	return 0;
}

void printWithoutUsingCharArray() {
    // Exercise Q3
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
    
    return;
}

void consoleToFile(){
    // Exercise Q2

    int maxSize;
    printf("Enter the max Size of buffer: ");
    scanf("%d", &maxSize);

    char *buffer = (char *)malloc((maxSize + 1) * sizeof(char));

    char ch;
    int counter = 0;

    printf("Enter $ to exit \n");
    do
    {   
        printf("Enter char: ");
        scanf("%c", &ch);
        buffer[counter++] = ch;
    } while (ch != '$');

    buffer[counter] = '\0';

    int fd = open("Sample.txt", O_WRONLY);
    write(fd, buffer, counter);


    for (int i = 0; i < buffer[i] != '\0'; ++i)
    {
        printf("%c", buffer[i]);
    }
    
    return;
}

void halfSize()
{
    // Exercise Q1;
    int fd;

    fd = open("Sample.txt", O_RDONLY);
    printf("%d\n", fd);

    int fileSize = lseek(fd, 0, SEEK_END);
    int halfSize = fileSize / 2;
    printf("%d\n", fileSize);
    printf("%d\n", halfSize);

    // Create buffer to store.
    char *buffer1 = (char *)malloc((halfSize + 1) * sizeof(char));
    char *buffer2 = (char *)malloc((halfSize + 1) * sizeof(char));

    // read half of the file.
    lseek(fd, 0, 0);
    int rd1 = read(fd, buffer1, halfSize);
    lseek(fd, 0, halfSize);
    int rd2 = read(fd, buffer2, halfSize);

    printf("%d %d\n", rd1, rd2);

    buffer1[rd1] = '\0';
    buffer2[rd2] = '\0';

    int newFd1 = open("Sample1.txt", O_CREAT | O_WRONLY, 0777);
    int newFd2 = open("Sample2.txt", O_CREAT | O_WRONLY, 0777);

    int wr1 = write(newFd1, buffer1, rd1);
    int wr2 = write(newFd2, buffer2, rd2);
}

void appendInFile()
{
    int n, m;

    char buffer[100];

    // write(fd, char[], len): Writes len bytes into fd file from char array.
    // return Number of bytes written on success
    // return 0 on reaching end of file
    // return -1 on error
    // return -1 on signal interrupt
    n = write(1, "HelloWorld", 10);

    printf("\nNo. of chars written : %d", n);

    // read(fd, char[], len): reads len bytes from fd and store into char array
    // return Number of bytes read on success
    // return 0 on reaching end of file
    // return -1 on error
    // return -1 on signal interrupt

    int readFromConsole, writeIntoFile;

    writeIntoFile = open("Sample.txt", O_WRONLY | O_APPEND);

    // readFromConsole stores the length of user input
    readFromConsole = read(0, buffer, 21);

    // append into file with lenght of user input.
    write(writeIntoFile, buffer, readFromConsole);

    return;
}

void openFile()
{
    int fd;
    // fd is file descriptor: An integer which identifies the open file of the process.

    // There are three standard file descriptor:
    // 0 : Read from stdin
    // 1 : Write to stdout
    // 2 : Write to stderr

    // Usually the first fd which is assigned to user is 3 because {0, 1, 2} are reserved.
    // Open functions returs a -1 when there is any error in opening file.

    char buffer[100];

    // Open file in read only mode.
    fd = open("Sample.txt", O_RDONLY);

    if (fd < 0)
    {
        perror("Error Opening the file");
        return;
    }

    printf("Opened file with descriptor: ");
    printf("%d\n", fd); // 3 : Default value of first fd availabe.'

    // read from stdin into buffer for 10 units
    read(0, buffer, 10);

    // write from buffer into console of length 10;
    write(1, buffer, 10);

    // Close(fd) : Used to close the descriptor.  Returns 0 on success and -1 on error.
    if (close(fd) == -1)
    {
        perror("Error Closing the file");
        return;
    }
}

void readFile()
{

    int fd;
    char buffer[12];

    // open file in read only mode.
    fd = open("Sample.txt", O_RDONLY);
    printf("%d\n", fd);

    // if the file does not exist, open() will genrate error and assign -1 to fd;
    // handle error.
    if (fd < 0)
    {
        // Prompt error:
        perror("open");
        printf("File does not Exist");
        return 0;
    }

    int ch = read(fd, buffer, 11);

    if (ch != 11)
    {
        perror("Read");
        printf("Error reading the file");
        return 0;
    }

    buffer[ch] = '\0';

    for (int i = 0; buffer[i] != '\0'; ++i)
    {
        printf("%c", buffer[i]);
    }

    printf("%s", buffer);

    close(fd);
}

void createWrite()
{

    int fd;
    char buffer[12] = "hell";

    // open file in read and write mode.
    fd = open("Dummy.txt", O_RDWR | O_CREAT);
    printf("%d\n", fd);

    // handle error.
    if (fd < 0)
    {
        // Prompt error:
        perror("open/create");
        return 1;
    }

    int ch = write(fd, buffer, 4);

    if (ch != 4)
    {
        perror("Read");
        printf("Error writing the file");
        return 1;
    }

    close(fd);
}

int main()
{

    practice();

    return 0;
}