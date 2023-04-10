// Roll RK21RXA26

// Name: Shubhansu Kumar Singh
// Section: RK21RX
// Reg. No: 12104991
// Question: Simulation Based 2

// Submitted To: Dr. Mohammad Faiz (28700).


/* 

Q2 - 

You are a computer systems engineer working at a large technology company. Your manager has 
tasked you with creating a simulation program to test the performance of the Shortest Job First 
scheduling algorithm. The simulation program should generate a set of "processes" with random 
arrival times and CPU burst times, and should run the Shortest Job First scheduling algorithm for a set 
amount of time (e.g. 100 time units). The program should record the average waiting time and 
turnaround time for each process, and should compare the results with the ideal scenario of a perfect 
scheduler. 
Your manager is interested in the results of the simulation to evaluate how well the Shortest Job First 
scheduling would perform in a real-world scenario, and to identify any potential issues that need to be 
addressed. She has given you one week to complete the simulation and to prepare a report of your 
findings and conclusions. As a computer systems engineer, you will need to: 
a) Design and implement the simulation program using a programming language of your choice.
b) Generate a set of "processes" with random arrival times and CPU burst times using a random 
number generator. 
c) Implement the Shortest Job First scheduling algorithm in the simulation program for both preemptive 
and non-pre-emptive processes. 
d) Have the simulation program run for a set amount of time (e.g. 100 time units) and record the 
average waiting time and turnaround time for each process using both pre-emptive and nonpre-emptive processes. 
e) Compare the results of the simulation with the ideal scenario of a perfect scheduler. 
f) Write a report of the findings and conclusion with the comparison of the results of the 
Shortest Job First scheduling algorithm with other scheduling algorithms such as First Come 
First Serve (FCFS) and Round Robin. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Process {
    int pId;
    int arrivalTime;
    int burstTime;
    int priority;
};


// Function: PrintResult(): 
// Inputs: Process array, completion time array, turn around time array, wait time array, toatalWt and total TAT
// Output: Prints the execution table along with avg wait time and avg Tat.
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

// Function: sortProcess(): 
// Inputs: Process array, size of array
// Outputs: Sorts the process array on the basis of arrival time. 
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

// Function: FCFS(): FirstComeFirstServe Schedule Simulation
// Inputs: Process Array, Size of Array
// Outputs: Returns the avg WT of the FCFS scheduling algo.
float FCFS(struct Process p[], int n) {
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

    // printResult(p, CT, TAT, WT, n, totalWT, totalTAT);
    return (float)totalWT/n;
}


// Function: SJF(): ShortestJobFirst Schedule Simulation
// Inputs: Process Array, Size of Array
// Outputs: Returns the avg WT of the SJF scheduling algo.
float SJF(struct Process p[], int n) {
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

    for (int i = 0; i < n; ++i)
    {
        p[i].burstTime = BT[i];
    }
    
    printf("\n\nExecution Result of ShortestJobFirst(NonPreemptive): \n");
    printResult(p, CT, TAT, WT, n, totalWT, totalTAT);
    // printf("\n");

    return (float)totalWT/n;
}

// Function: SRTF(): ShortestRemainingTimeFirst Schedule Simulation
// Inputs: Process Array, Size of Array
// Outputs: Returns the avg WT of the SRTF scheduling algo.
float SRTF(struct Process p[], int n) {
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

        currentTime++;

        if (index == -1) {
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

    }

    printf("\n\nExecution Result of ShortestRemainingTimeFirst(Preemptive): \n");
    printResult(p, CT, TAT, WT, n, totalWT, totalTAT);
    printf("\n");

    return (float)totalWT/n;
}

// Function: nonPremptivePriorityScheduling(): Schedule Simulation
// Inputs: Process Array, Size of Array
// Outputs: Returns the avg WT of the npps scheduling algo.
float nonPreemptivePriorityScheduling(struct Process p[], int n) {
    int WT[n], TAT[n], CT[n], completed[n];
    int totalWT = 0, totalTAT = 0, currentTime = 0, completedCount = 0;
    // printf("\nNPPS");

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

    // printResult(p, CT, TAT, WT, n, totalWT, totalTAT);
    return (float)totalWT/n;
}

// Function: preemptivePriorityScheduling(): Schedule Simulation
// Inputs: Process Array, Size of Array
// Outputs: Returns the avg WT of the PPS scheduling algo.
float preemptivePriorityScheduling(struct Process p[], int n) {
    int WT[n], TAT[n], remainingTime[n], CT[n];
    int totalWT = 0, totalTAT = 0, currentTime = 0, completedCount = 0;

    // printf("\nPPS");

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

    // printResult(p, CT, TAT, WT, n, totalWT, totalTAT);
    return (float)totalWT/n;
}

// Function: RR(): RoundRobin Schedule Simulation
// Inputs: Process Array, Size of Array
// Outputs: Returns the avg WT of the RR scheduling algo.
float roundRobin(struct Process p[], int n, int quantum) {

    // printf("\nRR");
    int remainingTime[n], WT[n], TAT[n], CT[n];
    int totalWT = 0, totalTAT = 0, currentTime = 0, completedCount = 0;

    for (int i = 0; i < n; i++) {
        remainingTime[i] = p[i].burstTime;
    }

    while (completedCount < n) {
        // printf("Hell");
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
            else {
                ++currentTime;
            }
        }
    }

    // printResult(p, CT, TAT, WT, n, totalWT, totalTAT);
    return (float)totalWT/n;
}

void chooseALGO(int index) {
    switch (index)
    {
    case 0:
        printf("FCFS: FirstComeFirstServe");
        break;
    case 1:
        printf("SJF: ShortestJobFirst");
        break;
    case 2:
        printf("SRTF: ShortestRemainingTimeFirst");
        break;
    case 3:
        printf("NPPS: NonPreemptivePriorityScheduling");
        break;
    case 4:
        printf("PPS: PreemptivePriorityScheduling");
        break;
    case 5:
        printf("RR: RoundRobin");
        break;
    default:
        printf("Error");
        break;
    }
}

// Function: ComparePerfectScheduler()
// Input: Result array, minIndex
// Output: Compares the average waittime of perfect scheduler with SJF and SRTF.
void comparePerfectScheduler(float result[], int minIndex) {

    printf("\n\n\nThe Perfect Scheduler with minimum AverageWaitingTime is: ");
    chooseALGO(minIndex);
    printf("\nThe minimum AverageWaitingTime is: %.2f\n", result[minIndex]);

    // Check if multiple algos have same wait time.
    int flag = 0;
    for (int i = 0; i < 6; ++i)
    {
        if (i == minIndex) continue;
        if (result[i] == result[minIndex]) {
            flag++;
        }
    }

    // Print all the algos with same wait time(min);
    if (flag) {
        printf("\nOther Algos with same min. average wait time are: ");
        for (int i = minIndex+1; i < 6; ++i)
        {
            if (result[i] == result[minIndex]) {
                chooseALGO(i);
                printf(" ");
            }
        }
        printf("\n");
    }

    // Compare the perfect scheduler with SJF and SRTF
    printf("\nAlgorithm   :\tSJF\tSRTF");
    printf("\nAvg.WaitTime:\t%.2f\t%.2f", result[1], result[2]);
    
    // Calculate the efficiency of SJF and SRTF
    float efficiencySJF, efficiencySRTF;
    
    efficiencySJF = result[minIndex]/result[1] * 100;
    efficiencySRTF = result[minIndex]/result[2] * 100;

    printf("\n\nEfficiency of SJF is  : %.2f %%", efficiencySJF);
    printf("\nEfficiency of SRTF is : %.2f %%", efficiencySRTF);
}


int main() {
    int n;

    printf("\nEnter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Create Process by taking input from user.

    /* 
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
    */

    // Create Process using random function 
    srand(time(0));
    for (int i = 0; i < n; ++i)
    {

        p[i].pId = i+1;

        // Take random arrival time for each process. Each process should have arrival time 
        // between 0 to 30;
        p[i].arrivalTime = (rand()*rand())%30;

        // Take random burstTime for each process. Each process should have burst time between 
        // 1 to 20;
        p[i].burstTime = 1 + (rand()*rand())%20;

        // setPriority of process: Again using the random function. 
        // Priority between 0 to 5;
        p[i].priority = (rand())%5;
    }
    
    // Once the process array is created, sort the array on the basis of arrival time 
    // for better scheduling time complexity.
    sortProcess(p, n);

    // Store the result of each Schedule algo
    // 0: FCFS | 1: SJF | 2: SRTF | 3: nonPreemptivePriority | 4: preemptivePriority | 5: RoundRobin
    float resultWT[6];

    resultWT[0] = FCFS(p, n);
    resultWT[1] = SJF(p, n);
    resultWT[2] = SRTF(p, n);
    resultWT[3] = nonPreemptivePriorityScheduling(p, n);
    resultWT[4] = preemptivePriorityScheduling(p, n);
    
    // Take user input for time Quantum of round robin.
    // int quantum;
    // printf("Enter the time quantum: ");
    // scanf("%d", &quantum); 

    // Or, just fix the time quantum to 5 units. 
    resultWT[5] = roundRobin(p, n, 5);

    printf("\n\tFCFS\tSJF\tSRTF\tNPPS\tPPS\tRR");
    printf("\nResult: ");
    for (int i = 0; i < 6; ++i)
    {
        printf("%.2f\t", resultWT[i]);
    }

    // Perfect Scheduler: The Scheduler with min. avg. wait time will be the perfect scheduler.

    float minWT = 2452342;
    int minWTIndex = -1;

    // Find the min. avg. wait time from the result.
    for (int i = 0; i < 6; ++i)
    {
        if (resultWT[i] < minWT) {
            minWT = resultWT[i];
            minWTIndex = i;
        }
    }

    // Compare the SJF and SRTF with perfect Scheduler.
    comparePerfectScheduler(resultWT, minWTIndex);
    
    printf("\n\n");
    
    return 0;
}
