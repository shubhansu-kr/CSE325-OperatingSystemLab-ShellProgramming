#include <stdio.h>

struct Process {
    int pId;
    int arrivalTime;
    int burstTime;
    int priority;
};

void nonPreemptivePriorityScheduling(struct Process p[], int n) {
    int WT[n], TAT[n], CT[n], completed[n];
    int totalWT = 0, totalTAT = 0, currentTime = 0, completedCount = 0;

    for(int i = 0; i < n; ++i) completed[i] = 0;

    while (completedCount < n) {
        int index = -1;
        int maxPriority = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && completed[i] == 0) {
                if (p[i].priority > maxPriority) {
                    index = i;
                    maxPriority = p[i].priority;
                }
            }
        }

        if (index == -1) {
            currentTime++;
            continue;
        }

        currentTime += p[index].burstTime;

        CT[index] = currentTime;

        TAT[index] = CT[index] - p[index].arrivalTime;
        totalTAT += TAT[index];


        WT[index] = TAT[index] - p[index].burstTime;
        totalWT += WT[index];

        completed[index] = 1;
        completedCount++;

    }

    printf("PID\tAT\tBT\tPriority\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", p[i].pId, p[i].arrivalTime, p[i].burstTime, p[i].priority, TAT[i], WT[i]);
    }

    float averageWT = (float)totalWT / n;
    float averageTAT = (float)totalTAT / n;

    printf("\nAverage waiting time: %.2f\n", averageWT);
    printf("Average turnaround time: %.2f\n", averageTAT);
}

void preemptivePriorityScheduling(struct Process p[], int n) {
    int WT[n], TAT[n], remainingTime[n], CT[n];
    int totalWT = 0, totalTAT = 0, currentTime = 0, completedCount = 0;

    // Initialize remaining burst time to burst time
    for (int i = 0; i < n; i++) {
        remainingTime[i] = p[i].burstTime;
    }

    while (completedCount < n) {
        int index = -1;
        int maxPriority = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && remainingTime[i] > 0) {
                if (p[i].priority > maxPriority) {
                    index = i;
                    maxPriority = p[i].priority;
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

            TAT[index] = CT[index] - p[index].arrivalTime;
            totalTAT += TAT[index];


            WT[index] = TAT[index] - p[index].burstTime;
            totalWT += WT[index];

            ++completedCount;
        }

        ++currentTime;
    }

    printf("PID\tAT\tBT\tPriority\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", p[i].pId, p[i].arrivalTime, p[i].burstTime, p[i].priority, TAT[i], WT[i]);
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
        printf("Priority: ");
        scanf("%d", &pcb[i].priority);
        printf("\n");

        pcb[i].pId = i + 1;
    }

    nonPreemptivePriorityScheduling(pcb, n);
    PreemptivePriorityScheduling(pcb, n);

    return 0;
}
