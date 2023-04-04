// MultiLevel Queue CPU Scheduling : Q1: Priority Q2: RoundRobin

// Concept: Whenever a process arrives, push the process in queue Q1. Compare with the
// priority of current process, IF the current process was from q1 else preempt process to
// q2 and start executing the newly arrived process.  

// Flow Chart: Take Input -> Complete Process -> Print Result. 

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

// define a comparison function to order processes by arrival time (least arrival time first
struct CompareAT {
    bool operator()(const Process& p1, const Process& p2) const {
        return p1.arrivalTime > p2.arrivalTime;
    }
};

// Take userInput for the use case. : Return the array of process.
// vector -> dynammic array like arrayList in java
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
// Once we take input from the user we push the processes in the arrival queue.
// So, that it can be sorted to get the least arrival time first.
void setArrivalQueue(vector<Process> &p, priority_queue<Process, vector<Process>, CompareAT> &q) {
    for(auto &it: p){q.push(it);}
}

// Simulation function: 
void simulate(int idle, int currentTime, Process currentProcess, queue<Process> q2, priority_queue<Process, vector<Process>, ComparePriority> q1) {
    cout << currentTime << " : " << currentProcess.id << endl;

    cout << "\tCurrentTime(ms): " << setw(10) << currentTime << endl;
    cout << endl;

    if (idle) {
        cout << "\n\tCPU is in idle state" << endl; 
        cout << "\n\n\n\tQ1: Empty" << endl;
        cout << "\tQ2: Empty" << endl;
    }
    else {
        cout << "\t                " << " pId" << " priority" << " arrivalTime" << " remainingTime " << endl; 
        cout << "\tCurrentProcess: " << setw(4) << currentProcess.id << setw(9) << currentProcess.priority << setw(12) << currentProcess.arrivalTime << setw(13) << currentProcess.remainingTime << endl;
    
        cout << "\n\n\tQ1: ";
        if (q1.empty()){
            cout << "Empty\n";
        }else {
            cout << "| ";
            while(!q1.empty()) {
                cout << "P" << q1.top().id << " | ";
                q1.pop();
            }
            cout << "\n";
        }

        cout << "\tQ2: ";
        if (q2.empty()){
            cout << "Empty\n";
        }else {
            cout << "| ";
            while(!q2.empty()){
                cout << "P" << q2.front().id << " | ";
                q2.pop();
            }
            cout << "\n";
        }

    
    }
}

int main() {
    // initialize the two priority queues for the two levels
    // We already discussed how priority queue works in c++ and by default it maked max heap
    // but we need min heap so we have to create a custom compare function
    // declared above named Compare Priority.
    priority_queue<Process, vector<Process>, ComparePriority> q1; // higher priority
    queue<Process> q2; // lower priority

    // Process vector recieved from user Input.
    vector<Process> p = createProcess();

    // Min. heap priority queue (Arrival time Priority)
    priority_queue<Process, vector<Process>, CompareAT> AT; 
    setArrivalQueue(p, AT);

    // Vector to store gantt chart
    // array of pairs.
    // Pair is a data structure which has two values pair.first and pair.second.
    // so this vector represents a 2d matrix with n rows and 2 fixed columns.

    // in gant chart we will record current time and process id. 2 variables to be stored 
    // that's why we are using pairs. 
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

    // execute processes until both queues are empty, arrival Queue is empty and cpu is idle.
    while (!AT.empty() || !q1.empty() || !q2.empty() || !idle) {
        system("cls");
    
        // 1. Arrival Cycle. : First part: See if any processes arrive and update the queue.

        // Check if a new process arrived. (compare arrival time with currentTime)
        // push the process(if any arrived) in the q1 queue and pop from arrival queue.
        while(!AT.empty() && currentTime >= AT.top().arrivalTime) {
            q1.push(AT.top());
            AT.pop();
        }

        // Once process have arrived in the queue. Check if the current process's priority
        // is higher or lower. 
        // if priority in lower : preempt otherwise ignore.
        // CPU can be in two states at this moment : 1. Idle 2. Executing.
        // Idle means the current process was null. So no need to compare just set the newly
        // arrived process as current process.
        // If Not ilde. simple comparison of priorities.

        // Two Variables used: 1. idle: Tells if cpu is idle or not. 
        // 2. flag: Tells if the process was from q1 or q2. flag = 0 represents q1 and flag = 1 represents q2
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

        // Keep taking snapshots of state of cpu after arrival cycle. 
        // To construct the gantt chart later.
        // Void Simulate() : Print Inter mediate.  
        simulate(idle, currentTime, currentProcess, q2, q1);       

        // emplace back is just like push. 
        // this func pushes the value of CT and PID in array.
        gc.emplace_back(pair<int, int>({currentTime, currentProcess.id}));

        // Execution cycle.
        // By this step, we have compared the arrived process, currentprocess, and all the other
        // parameters to choose the currentProcess to be executed. 
        // There can be 2 case after arrival cycle(selection of process) : either no process arrived and
        // cpu will be idle or we got a process to execute.

        // if idle, skip the execution cycle, just increment the currenttime counter.        
        if (idle) {
            currentTime++;

            // skip cycle.
            continue;
        }

        // Now if we are at this point, it means we have a process to execute.
        // But there are stll 2 cases. If the process was loaded from q1, Time quantum will be of 
        // 1 second  and if the process was loaded from q2 Time quantum will be of 2 sec.

        // To check which queue loaded the process, we used a flag variable. 
        // flag = 0 : means q1
        // flag = 1 : means q2 
        // we already took care of flag above. so we can assume it is correctly 
        // telling us the state. 

        // if flag = 0: time quantum should be 1 which is (1 + 0): which is (1 + flag)
        // if flag = 1: time quantum should be 2 which is (1 + 1): which is (1 + flag)
        // used in the next line. 

        // This you already know how it's done.
        // choose min. between rem. time and burst time and update the varibales. 
        // execute the current process for a multiple of 2 time units
        int timeSlice = min(1+flag, currentProcess.remainingTime);
        currentProcess.remainingTime -= timeSlice;
        currentProcess.executedTime += timeSlice;
        currentTime += timeSlice;

        // lastSlice used for gantChart calculation.
        lastSlice = timeSlice;


        // After execution we need to check if current process was completed or not
        // Completion cycle. 
        
        // if process was completed, load current process from q1, if q1 will be empty, load from q2
        // if q2 will also be empty, set cpu as idle. 

        // if process was not idle but we were executing the q2 queue(round robin): (check using flag variable)
        // we will dequeue and enquqe to simulate roundrobin. 

        // store the result in array if process completes.
        // Current time becomes completion time of process.

        // we used a 2d matrix to store the result. where each row represents process and columns 
        // represents attributes like priority, pid, at, ct, ... etc.

        // like this. declared above.

        // vector<vector<int>> result(n, vector<int>(6, -1)); // priority, at, bt, ct, tat, wt

        // This syntax is not alien. 
        // vector is a class. <int> is template specifier which tells the compiler we need int vector
        // result is the name of the matrix
        // and (n, vector<int>(6, -1)) : is constructor call. which creates n rows and in each row 
        // 6 column with each cell value -1;

        // So, by this line we get a 2d matrix with n rows 6 columns each cell initialised with -1;
        // Simple :)

        

        // check if the current process has finished: Situation explained above: simple code
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
            // dequeue -> enqueue
            if (flag) {
                q2.push(currentProcess);
                currentProcess = q2.front();
                q2.pop();
            }
        }

        Sleep(3000);
        system("cls");

    }

    // Successfull Execution: Evaluate performance.
    // Once we have our results. Take sum of Wait time and Turn around time
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
        // setw is used to set the printing width on concole.
        cout << setw(3) << i + 100 << setw(11) << result[i][0] << setw(6) << result[i][1] << setw(6) << result[i][2] << setw(6) << result[i][3] << setw(8) << result[i][4] << setw(6) << result[i][5] << endl;
    }
    cout << "\n";
    cout << "Average Turn Around Time: " << AverageTAT << " ms" << endl;
    cout << "Average Wait Time: " << AverageWT << " ms" << endl;
    cout << "\n";
    
    cout << "Gantt Chart: \n\n";
    cout << " Time(ms)\tProcess\n";


    // Calculate gantt chart: Just club all the same process together and print.
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