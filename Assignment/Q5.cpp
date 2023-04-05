// Multi Queue Round Robin

#include <bits/stdc++.h>
using namespace std ;

struct Process {
    int id;
    int priority;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int executedTime;
};

int pId = 100;

vector<Process> createProcess() {
    int n;
    cout << "Enter the number of process: ";
    cin >> n;

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
        cout << "Enter arrivalTime [0-120): ";
        cin >> p[i].arrivalTime;
        cout << "Enter burstTime: ";
        cin >> p[i].burstTime;
        cout << "Enter priority(1: Teacher | 0: Student): ";
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