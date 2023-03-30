#include <stdio.h>

struct Process {
    int pId;
    int arrivalTime;
    int burstTime;
    int priority;
};


void printResult(struct Process p[], int CT[], int TAT[], int WT[], int n, int totalWT, int totalTAT){
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


void sortProcess(struct Process p[], int n) {
    for (int i = 0; i < n; ++i)
    {
        struct Process mini;
        mini.arrivalTime = __INT_MAX__;
        int index = i;

        for (int j = i; j < n; ++j)
        {
            if (mini.arrivalTime > p[j].arrivalTime) {
                mini = p[j];
                index = j;
            }
        }

        // swap i, minJ
        mini = p[i];
        p[i] = p[index];
        p[index] = mini;        
    }
    
}


void FCFS(struct Process p[], int n) {
    int WT[n], TAT[n], CT[n];

    int totalWT = 0, totalTAT = 0, currentTime = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].arrivalTime) {
            currentTime = p[i].arrivalTime;
        }


        currentTime += p[i].burstTime;

        CT[i] = currentTime;

        TAT[i] = CT[i] - p[i].arrivalTime;
        totalTAT += TAT[i];

        WT[i] = TAT[i] - p[i].burstTime;
        totalWT += WT[i];
    }

   printResult(p, CT, TAT, WT, n, totalWT, totalTAT);
}


void SJF(struct Process p[], int n) {
    int WT[n], TAT[n], CT[n], BT[n];
    int totalWT = 0, totalTAT = 0, currentTime = 0, completedCount = 0;

    while (completedCount < n) {
        int index = -1;
        int minBT = __INT_MAX__;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime) {
                if (p[i].burstTime < minBT) {
                    index = i;
                    minBT = p[i].burstTime;
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

        BT[index] = p[index].burstTime;
        p[index].burstTime = __INT_MAX__;

        ++completedCount;
    }

    printResult(p, CT, TAT, WT, n, totalWT, totalTAT);
}


void SRTF(struct Process p[], int n) {
    int WT[n], TAT[n], remainingTime[n], CT[n];
    int totalWT = 0, totalTAT = 0, currentTime = 0, completedCount = 0;

    // Initialize remaining burst time to burst time
    for (int i = 0; i < n; i++) {
        remainingTime[i] = p[i].burstTime;
    }

    while (completedCount < n) {
        int index = -1;
        int minBT = __INT_MAX__;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && remainingTime[i] > 0) {
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

            TAT[index] = CT[index] - p[index].arrivalTime;
            totalTAT += TAT[index];

            WT[index] = TAT[index] - p[index].burstTime;
            totalWT += WT[index];

            ++completedCount;
        }

        ++currentTime;
    }

    printResult(p, CT, TAT, WT, n, totalWT, totalTAT);
}


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

    printResult(p, CT, TAT, WT, n, totalWT, totalTAT);
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

    printResult(p, CT, TAT, WT, n, totalWT, totalTAT);
}


void roundRobin(struct Process p[], int n, int quantum) {
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

    printResult(p, CT, TAT, WT, n, totalWT, totalTAT);
}


int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    printf("Enter the arrival time and burst time of each process:\n\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);

        printf("\n\nArrivalTime: ");
        scanf("%d", &p[i].arrivalTime);
        printf("BurstTime: ");
        scanf("%d", &p[i].burstTime);
        printf("\n");

        p[i].pId = i + 1;
    }

    sortProcess(p, n);

    FCFS(p, n);
    SJF(p, n);
    SRTF(p, n);
    nonPreemptivePriorityScheduling(p, n);
    preemptivePriorityScheduling(p, n);

    int quantum;

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);  

    roundRobin(p, n, quantum);

    return 0;
}
