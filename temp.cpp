// Round Robin: 

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// define a struct to represent a process
struct Process {
    int id;
    int priority;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int executed_time;
};

// define a comparison function to order processes by priority (higher priority first)
struct ComparePriority {
    bool operator()(const Process& p1, const Process& p2) const {
        return p1.priority < p2.priority;
    }
};

void createProcess() {
    int n;
    cout << "Enter the number of process: ";
    cin >> n;

    
}

int main() {
    // initialize the two priority queues for the two levels
    priority_queue<Process, vector<Process>, ComparePriority> q1; // higher priority
    queue<Process> q2; // lower priority

    // add some sample processes to the higher priority queue (queue 1)
    q1.push({1, 0, 0, 8, 8, 0});
    q1.push({2, 0, 1, 10, 10, 0});
    q1.push({3, 0, 0, 6, 6, 0});

    q1.push({4, 0, 2, 7, 7, 0});

    int current_time = 0; // current time in the simulation
    Process current_process; // current process being executed

    // execute processes until both queues are empty
    while (!q1.empty() || !q2.empty()) {
        // check if there's a higher priority process waiting in queue 1
        if (!q1.empty() && q1.top().priority < current_process.priority) {
            // preempt the current process and move it to queue 2
            q2.push(current_process);
            current_process = q1.top();
            q1.pop();
        }

        // execute the current process for a multiple of 2 time units
        int time_slice = min(2, current_process.remaining_time);
        current_process.remaining_time -= time_slice;
        current_process.executed_time += time_slice;
        current_time += time_slice;

        // check if the current process has finished
        if (current_process.remaining_time == 0) {
            cout << "Process " << current_process.id << " finished at time " << current_time << endl;
            current_process = Process(); // reset the current process

            // check if there's another process waiting in queue 1
            if (!q1.empty()) {
                current_process = q1.top();
                q1.pop();
            } else if (!q2.empty()) {
                // move the processes in queue 2 to the end of queue 1
                while (!q2.empty()) {
                    q2.front().priority++; // decrease priority for round robin
                    q1.push(q2.front());
                    q2.pop();
                }
            }
        } else if (current_process.executed_time % 6 == 0) {
            // move the current process to the end of queue 2 for round robin
            current_process.priority++;
            q2.push(current_process);
            current_process = Process(); // reset the current process

            // check if there's another process waiting in queue 1
            if (!q1.empty()) {
                current_process = q1.top();
                q1.pop();
            }
        }
    }

    return 0;
}