#include <stdio.h>

#define MAX_PROCESSES 100

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

void round_robin(struct Process p[], int n, int quantum) {
    int remaining_time[MAX_PROCESSES];
    int completed[MAX_PROCESSES] = {0};
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;
    int completed_count = 0;

    for (int i = 0; i < n; i++) {
        remaining_time[i] = p[i].burst_time;
    }

    while (completed_count < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && remaining_time[i] > 0) {
                if (remaining_time[i] <= quantum) {
                    current_time += remaining_time[i];
                    p[i].turnaround_time = current_time - p[i].arrival_time;
                    p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
                    total_waiting_time += p[i].waiting_time;
                    total_turnaround_time += p[i].turnaround_time;
                    remaining_time[i] = 0;
                    completed_count++;
                } else {
                    current_time += quantum;
                    remaining_time[i] -= quantum;
                }
            }
        }
    }

    printf("PID\tAT\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }

    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;

    printf("Average waiting time: %.2f\n", avg_waiting_time);
    printf("Average turnaround time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n, quantum;
    struct Process p[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the arrival time and burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        p[i].pid = i + 1;
        p[i].remaining_time = p[i].burst_time;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    round_robin(p, n, quantum);

    return 0;
}
