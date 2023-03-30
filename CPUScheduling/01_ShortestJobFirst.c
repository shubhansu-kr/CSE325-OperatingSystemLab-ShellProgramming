#include <stdio.h>

#define MAX_PROCESSES 100

struct Process
{
    int pId;
    int arrivalTime;
    int burstTime;
};

void sortProcess(struct Process pcb[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        struct Process mini;
        mini.burstTime = __INT_MAX__;
        int index = i;

        for (int j = i; j < n; ++j)
        {
            if (mini.burstTime > pcb[j].burstTime || mini.burstTime == pcb[j].burstTime && mini.arrivalTime > pcb[j].arrivalTime)
            {
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

void SJF(struct Process pcb[], int n)
{
    int WT[n], TAT[n], CT[n], AT[n];

    int totalWT = 0, totalTAT = 0, currentTime = 0;

    for (int i = 0; i < n; i++)
    {

        int index = -1;

    // select Process.
    A:
        for (int j = 0; j < n; ++j)
        {
            if (currentTime >= pcb[j].arrivalTime)
            {
                index = j;
                break;
            }
        }

        if (index == -1)
        {
            ++currentTime;
            goto A;
        }

        currentTime += pcb[index].burstTime;

        CT[index] = currentTime;

        TAT[index] = CT[index] - pcb[index].arrivalTime;
        totalTAT += TAT[index];

        WT[index] = TAT[index] - pcb[index].burstTime;
        totalWT += WT[index];

        // Remove process from scope.
        AT[index] = pcb[index].arrivalTime;
        pcb[index].arrivalTime = __INT_MAX__;
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pcb[i].pId, AT[i], pcb[i].burstTime, CT[i], TAT[i], WT[i]);
    }

    float averageWT = (float)totalWT / n;
    float averageTAT = (float)totalTAT / n;

    printf("\nAverage waiting time: %.2f\n", averageWT);
    printf("Average turnaround time: %.2f\n", averageTAT);
}

void SJF1(struct Process pcb[], int n) {
    int WT[n], TAT[n], CT[n], BT[n];
    int totalWT = 0, totalTAT = 0, currentTime = 0, completedCount = 0;

    while (completedCount < n) {
        int index = -1;
        int minBT = __INT_MAX__;

        for (int i = 0; i < n; i++) {
            if (pcb[i].arrivalTime <= currentTime) {
                if (pcb[i].burstTime < minBT) {
                    index = i;
                    minBT = pcb[i].burstTime;
                }
            }
        }

        if (index == -1) {
            currentTime++;
            continue;
        }


        currentTime += pcb[index].burstTime;

        CT[index] = currentTime;

        TAT[index] = CT[index] - pcb[index].arrivalTime;
        totalTAT += TAT[index];

        WT[index] = TAT[index] - pcb[index].burstTime;
        totalWT += WT[index];

        BT[index] = pcb[index].burstTime;
        pcb[index].burstTime = __INT_MAX__;

        ++completedCount;
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pcb[i].pId, pcb[i].arrivalTime, BT[n], CT[i], TAT[i], WT[i]);
    }

    float averageWT = (float)totalWT / n;
    float averageTAT = (float)totalTAT / n;

    printf("\nAverage waiting time: %.2f\n", averageWT);
    printf("Average turnaround time: %.2f\n", averageTAT);
}

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process pcb[n];

    printf("\nEnter the arrival time and burst time of each process:\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);

        printf("\n\nArrivalTime: ");
        scanf("%d", &pcb[i].arrivalTime);
        printf("BurstTime: ");
        scanf("%d", &pcb[i].burstTime);
        printf("\n");

        pcb[i].pId = i + 1;
    }

    sortProcess(pcb, n);

    SJF(pcb, n);

    return 0;
}
