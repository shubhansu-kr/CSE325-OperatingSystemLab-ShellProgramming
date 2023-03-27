// Cpu Scheduling: 

#include <stdio.h>

struct Process {
    int id;
    int priority;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int executedTime;
};

int pId = 100;

Process* createProcess() {
    int n;
    printf("Enter the number of process: ");
    scanf("%d", &n);

    // Create an array of process(obj).
    vector<Process> p(n);

    for (int i = 0; i <= n; ++i)
    {
    
        // clear screen for each input.
        system("cls"); 

        if (i == n) break;

        // allocate processId 
        p[i].id = pId++;

        cout << "Process Id : " << p[i].id << endl << "\n";

        // Take input: Arrival time, Burst time, Priority of the process.
        cout << "Enter arrivalTime: ";
        cin >> p[i].arrivalTime;
        cout << "Enter burstTime: ";
        cin >> p[i].burstTime;
        cout << "Enter priority: ";
        cin >> p[i].priority;

        // Set remaining time and executed time.
        p[i].remainingTime = p[i].burstTime;
        p[i].executedTime = 0;
    }

    return p;
}

int main () {
    
    return 0;
}