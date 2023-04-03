// MultiLevel Queue CPU Scheduling : Q1: Priority Q2: RoundRobin

#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

// define a struct to represent a process
struct Process {
    int id;
    int priority;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int executedTime;
};

// Create a global variable(static) to assign pId.
int pId = 100;

// define a comparison function to order processes by priority (higher priority first)
struct ComparePriority {
    bool operator()(const Process& p1, const Process& p2) const {
        return p1.priority > p2.priority;
    }
};

struct CompareAT {
    bool operator()(const Process& p1, const Process& p2) const {
        return p1.arrivalTime > p2.arrivalTime;
    }
};

// Take userInput for the use case.
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

// Insert Process in Arrival Queue(Priority Based).
void setArrivalQueue(vector<Process> &p, priority_queue<Process, vector<Process>, CompareAT> &q) {
    for(auto &it: p){q.push(it);}
}

int main() {
    // initialize the two priority queues for the two levels
    priority_queue<Process, vector<Process>, ComparePriority> q1; // higher priority
    queue<Process> q2; // lower priority

    // Process vector recieved from user Input.
    vector<Process> p = createProcess();

    // Min. heap priority queue (Arrival time Priority)
    priority_queue<Process, vector<Process>, CompareAT> AT; 
    setArrivalQueue(p, AT);

    // Vector to store gantt chart
    vector<pair<int, int>> gc;

    // No. of processes.
    int n = p.size();

    // Array to store the final result of execution.
    vector<vector<int>> result(n, vector<int>(6, -1)); // priority, at, bt, ct, tat, wt

    int currentTime = 0; // current time in the simulation
    int idle = 1;        // initially cpu is idle. 
    int flag = 0;        // initially q1 is expected.

    int lastSlice = 0;

    Process currentProcess = Process(); // current process being executed

    // execute processes until both queues are empty
    while (!AT.empty() || !q1.empty() || !q2.empty() || !idle) {
        // Arrival Cycle.

        // Check if a new process arrived.
        while(!AT.empty() && currentTime >= AT.top().arrivalTime) {
            q1.push(AT.top());
            AT.pop();
        }

        if (!q1.empty()) {
            if (idle) {
                idle = 0;
                flag = 0;
                currentProcess = q1.top();
                q1.pop();
            }
            else if (currentProcess.priority > q1.top().priority) {
                flag = 0;
                q2.push(currentProcess);
                currentProcess = q1.top();
                q1.pop();
            }
        }

        // cout << currentTime << " : " << currentProcess.id << endl;
        gc.emplace_back(pair<int, int>({currentTime, currentProcess.id}));

        // Execution cycle.
        
        if (idle) {
            currentTime++;
            continue;
        }

        // execute the current process for a multiple of 2 time units
        int timeSlice = min(1+flag, currentProcess.remainingTime);
        currentProcess.remainingTime -= timeSlice;
        currentProcess.executedTime += timeSlice;
        currentTime += timeSlice;

        lastSlice = timeSlice;

        // check if the current process has finished
        if (currentProcess.remainingTime == 0) {
            cout << "Process " << currentProcess.id << " finished at time " << currentTime << endl;

            int index = currentProcess.id-100;
            result[index][0] = currentProcess.priority;
            result[index][1] = currentProcess.arrivalTime;
            result[index][2] = currentProcess.burstTime;
            result[index][3] = currentTime;

            currentProcess = Process(); // reset the current process

            // check if there's another process waiting in queue 1
            if (!q1.empty()) {
                flag = 0;
                currentProcess = q1.top();
                q1.pop();
            }
            // check if there's another process waiting in queue 2
            else if (!q2.empty()) {
                flag = 1;
                currentProcess = q2.front();
                q2.pop();
            }
            // Check if cpu is going idle.
            else {
                idle = 1;
                flag = 0;
            }
        }
        else {
            // Process is not completed but it was from round robin. so we need to change
            if (flag) {
                q2.push(currentProcess);
                currentProcess = q2.front();
                q2.pop();
            }
        }

    }

    // Successfull Execution: Evaluate performance.
    float TATSum = 0, WTSum = 0;
    for (int i = 0; i < n; ++i)
    {
        // TAT = CT - AT
        result[i][4] = result[i][3] - result[i][1];
        result[i][5] = result[i][4] - result[i][2];

        TATSum += result[i][4];
        WTSum += result[i][5];
    }
    
    float AverageTAT = (float)TATSum/n, AverageWT = (float)WTSum/n;

    cout << "\n\n";

    cout << "PID | Priority | A.T | B.T | C.T | T.A.T | W.T \n\n";
    for (int i = 0; i < n; ++i)
    {

        cout << setw(3) << i + 100 << setw(11) << result[i][0] << setw(6) << result[i][1] << setw(6) << result[i][2] << setw(6) << result[i][3] << setw(8) << result[i][4] << setw(6) << result[i][5] << endl;
    }
    cout << "\n";
    cout << "Average Turn Around Time: " << AverageTAT << " ms" << endl;
    cout << "Average Wait Time: " << AverageWT << " ms" << endl;
    cout << "\n";
    
    cout << "Gantt Chart: \n\n";
    cout << " Time(ms)\tProcess\n";

    int prev = 0;

    for(int i = 1; i < gc.size(); ++i) {

        if (gc[i].second != gc[i-1].second) {
            if (gc[i-1].second == 0) {
                cout << setw(3) << prev << " - " << setw(3) << gc[i-1].first + 1 << "\t" << setw(7) << "idle" << endl;
            }
            else {
                cout << setw(3) << prev << " - " << setw(3) << gc[i-1].first + 1 << "\t" << setw(4) << "p" << gc[i-1].second << endl;
            }
            prev = gc[i-1].first + 1;
        }
    }
    cout << setw(3) << prev << " - " << setw(3) << gc[gc.size()-1].first + lastSlice << "\t" << setw(4) << "P" << gc[gc.size()-1].second << endl;
 
    return 0;
}