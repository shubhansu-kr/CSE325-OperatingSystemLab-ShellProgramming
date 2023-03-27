#include <stdio.h>

#define MAX_PROCESSES 100

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
};

void FCFS(struct Process p[], int n) {
    int waiting_time[MAX_PROCESSES];
    int turnaround_time[MAX_PROCESSES];
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival_time) {
            current_time = p[i].arrival_time;
        }

        waiting_time[i] = current_time - p[i].arrival_time;
        total_waiting_time += waiting_time[i];

        current_time += p[i].burst_time;

        turnaround_time[i] = current_time - p[i].arrival_time;
        total_turnaround_time += turnaround_time[i];
    }

    printf("PID\tAT\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, waiting_time[i], turnaround_time[i]);
    }

    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;

    printf("Average waiting time: %.2f\n", avg_waiting_time);
    printf("Average turnaround time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;
    struct Process p[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the arrival time and burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        p[i].pid = i + 1;
    }

    FCFS(p, n);

    return 0;
}
