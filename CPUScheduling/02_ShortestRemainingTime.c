#include <stdio.h>

#define MAX_PROCESSES 100

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
};

void SRTF(struct Process p[], int n) {
    int waiting_time[MAX_PROCESSES];
    int turnaround_time[MAX_PROCESSES];
    int remaining_burst_time[MAX_PROCESSES];
    int completed[MAX_PROCESSES] = {0};
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;
    int completed_count = 0;

    // Initialize remaining burst time to burst time
    for (int i = 0; i < n; i++) {
        remaining_burst_time[i] = p[i].burst_time;
    }

    while (completed_count < n) {
        int shortest_job_index = -1;
        int shortest_job_burst_time = 1000000;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && completed[i] == 0) {
                if (remaining_burst_time[i] < shortest_job_burst_time) {
                    shortest_job_index = i;
                    shortest_job_burst_time = remaining_burst_time[i];
                }
            }
        }

        if (shortest_job_index == -1) {
            current_time++;
            continue;
        }

        remaining_burst_time[shortest_job_index]--;

        if (remaining_burst_time[shortest_job_index] == 0) {
            waiting_time[shortest_job_index] = current_time - p[shortest_job_index].arrival_time - p[shortest_job_index].burst_time + 1;
            total_waiting_time += waiting_time[shortest_job_index];

            turnaround_time[shortest_job_index] = current_time - p[shortest_job_index].arrival_time;
            total_turnaround_time += turnaround_time[shortest_job_index];

            completed[shortest_job_index] = 1;
            completed_count++;
        }

        current_time++;
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

    SRTF(p, n);

    return 0;
}
