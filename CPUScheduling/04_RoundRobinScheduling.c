#include <stdio.h>
struct Process {
    int pId;
    int arrivalTime;
    int burstTime;
};

void round_robin(struct Process p[], int n, int quantum) {
    int remainingTime[n], WT[n], TAT[n], CT[n];
    int totalWT = 0, totalTAT = 0, currentTime = 0, completedCount = 0;

    for (int i = 0; i < n; i++) {
        remainingTime[i] = p[i].burstTime;
    }

    while (completedCount < n) {

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && remainingTime[i] > 0) {
                if (remainingTime[i] <= quantum) {
                    currentTime += remainingTime[i];

                    CT[i] = currentTime;

                    TAT[i] = CT[i] - p[i].arrivalTime;
                    totalTAT += TAT[i];

                    WT[i] = TAT[i] - p[i].burstTime;
                    totalWT += WT[i];

                    remainingTime[i] = 0;
                    completedCount++;

                } else {
                    currentTime += quantum;
                    remainingTime[i] -= quantum;
                }
            }
        }
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pId, p[i].arrivalTime, p[i].burstTime, CT[i], TAT[i], WT[i]);
    }

    float averageWT = (float)totalWT / n;
    float averageTAT = (float)totalTAT / n;

    printf("\nAverage waiting time: %.2f\n", averageWT);
    printf("Average turnaround time: %.2f\n", averageTAT);
}

int main() {
    int n, quantum;

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

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);    

    round_robin(pcb, n, quantum);

    return 0;
}
