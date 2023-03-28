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

void FCFS(struct Process pcb[], int n) {
    int WT[n], TAT[n], CT[n];

    int totalWT = 0, totalTAT = 0, currentTime = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < pcb[i].arrivalTime) {
            currentTime = pcb[i].arrivalTime;
        }


        currentTime += pcb[i].burstTime;

        CT[i] = currentTime;

        TAT[i] = CT[i] - pcb[i].arrivalTime;
        totalTAT += TAT[i];

        WT[i] = TAT[i] - pcb[i].burstTime;
        totalWT += WT[i];
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
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

    FCFS(pcb, n);

    return 0;
}
