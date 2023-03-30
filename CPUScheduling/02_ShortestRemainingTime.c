#include <stdio.h>

struct Process {
    int pId;
    int arrivalTime;
    int burstTime;
};

void sortProcess(struct Process pcb[], int n) {
    for (int i = 0; i < n; ++i)
    {
        struct Process mini;
        mini.arrivalTime = __INT_MAX__;
        int index = i;

        for (int j = i; j < n; ++j)
        {
            if (mini.arrivalTime > pcb[j].arrivalTime) {
                mini = pcb[j];
                index = j;
            }
        }

        // swap i, minJ
        mini = pcb[i];
        pcb[i] = pcb[index];
        pcb[index] = mini;        
    }
    
}

void SRTF(struct Process pcb[], int n) {
    int WT[n], TAT[n], remainingTime[n], CT[n];
    int totalWT = 0, totalTAT = 0, currentTime = 0, completedCount = 0;

    // Initialize remaining burst time to burst time
    for (int i = 0; i < n; i++) {
        remainingTime[i] = pcb[i].burstTime;
    }

    while (completedCount < n) {
        int index = -1;
        int minBT = __INT_MAX__;

        for (int i = 0; i < n; i++) {
            if (pcb[i].arrivalTime <= currentTime && remainingTime[i] > 0) {
                if (remainingTime[i] < minBT) {
                    index = i;
                    minBT = remainingTime[i];
                }
            }
        }

        if (index == -1) {
            currentTime++;
            continue;
        }

        remainingTime[index]--;

        // Process Completion
        if (remainingTime[index] == 0) {

            CT[index] = currentTime;

            TAT[index] = CT[index] - pcb[index].arrivalTime;
            totalTAT += TAT[index];


            WT[index] = TAT[index] - pcb[index].burstTime;
            totalWT += WT[index];

            ++completedCount;
        }

        ++currentTime;
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pcb[i].pId, pcb[i].arrivalTime, pcb[i].burstTime, CT[i], TAT[i], WT[i]);
    }

    float averageWT = (float)totalWT / n;
    float averageTAT = (float)totalTAT / n;

    printf("\nAverage waiting time: %.2f\n", averageWT);
    printf("Average turnaround time: %.2f\n", averageTAT);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process pcb[n];

    printf("Enter the arrival time and burst time of each process:\n\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);

        printf("\n\nArrivalTime: ");
        scanf("%d", &pcb[i].arrivalTime);
        printf("BurstTime: ");
        scanf("%d", &pcb[i].burstTime);
        printf("\n");

        pcb[i].pId = i + 1;
    }

    sortProcess(pcb, n);

    SRTF(pcb, n);

    return 0;
}