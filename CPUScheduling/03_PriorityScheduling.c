#include <stdio.h>

#define MAX_PROCESSES 100

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
};

void priority_scheduling(struct Process p[], int n) {
    int waiting_time[MAX_PROCESSES];
    int turnaround_time[MAX_PROCESSES];
    int completed[MAX_PROCESSES] = {0};
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;
    int completed_count = 0;

    while (completed_count < n) {
        int highest_priority_index = -1;
        int highest_priority = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && completed[i] == 0) {
                if (p[i].priority > highest_priority) {
                    highest_priority_index = i;
                    highest_priority = p[i].priority;
                }
            }
        }

        if (highest_priority_index == -1) {
            current_time++;
            continue;
        }

        waiting_time[highest_priority_index] = current_time - p[highest_priority_index].arrival_time;
        total_waiting_time += waiting_time[highest_priority_index];

        turnaround_time[highest_priority_index] = current_time - p[highest_priority_index].arrival_time + p[highest_priority_index].burst_time;
        total_turnaround_time += turnaround_time[highest_priority_index];

        completed[highest_priority_index] = 1;
        completed_count++;

        current_time += p[highest_priority_index].burst_time;
    }

    printf("PID\tAT\tBT\tPriority\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority, waiting_time[i], turnaround_time[i]);
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

    printf("Enter the arrival time, burst time and priority of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
        p[i].pid = i + 1;
    }

    priority_scheduling(p, n);

    return 0;
}
