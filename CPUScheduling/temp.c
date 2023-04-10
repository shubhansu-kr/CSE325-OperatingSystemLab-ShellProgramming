#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int i;
    
    // Seed the random number generator with the current time
    srand(time(NULL));
    
    // Generate and print a random number in each loop iteration
    for (i = 0; i < 10; i++) {
        int random_number = rand();
        printf("Random number %d: %d\n", i+1, random_number);
    }
    
    return 0;
}
