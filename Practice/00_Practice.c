// Simulate the following hierarchy 
//               P1
//            /    \
//          P2       P5
//          |        |
//          P3       P6
//          |        |
//          P4       P7

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{

    pid_t pid2, pid5;

    pid2 = fork();

    if (pid2 < 0)
    {
        return 0;
    }
    else if (pid2 == 0)
    {
        // P2 (child P1);

        // Create Child P3
        pid_t pid3 = fork();

        if (pid3 < 0)
        {
            return 0;
        }
        else if (pid3 == 0)
        {
            // P3 (child of P2)

            pid_t pid4 = fork();

            if (pid4 < 0)
            {
                return 0;
            }
            else if (pid4 == 0)
            {
                // P4 (child of P3)

                // P4 as orphan process 
                // Put child to sleep;

                sleep(10);
            }
            else
            {
                // P3 Execution
            }
        }
        else
        {
            // P2 Execution
        }
    }
    else
    {
        // P1 (parent process)

        pid5 = fork();
        if (pid5 < 0)
        {
            return 0;
        }
        else if (pid5 == 0)
        {
            // P5 (child P1)

            // Create Child P6
            pid_t pid6 = fork();

            if (pid6 < 0)
            {
                return 0;
            }
            else if (pid6 == 0)
            {
                // P6 (child of P5)

                pid_t pid7 = fork();

                if (pid7 < 0)
                {
                    return 0;
                }
                else if (pid7 == 0)
                {
                    // P7 (child of P6)
    
                    // P7 as zombie. 
                    // Put parent(P6) to sleep.
                }
                else
                {
                    // P6 Execution
                    sleep(10);
                }
            }
            else
            {
                // P5 Execution
            }
        }
        else
        {
            // P1 
        }
    }

    return 0;
}