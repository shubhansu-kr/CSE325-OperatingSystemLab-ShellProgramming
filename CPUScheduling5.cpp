#include <bits/stdc++.h>
using namespace std;

class Request
{
public:
    int process_id;
    string name;
    char person;
    int atime;
    int btime;
    int remaining_time;
    void getInputs(int id);

    Request() {}
    Request(int process_id, string name, char person, int atime, int btime)
    {
        this->process_id = process_id;
        this->name = name;
        this->person = person;
        this->atime = atime;
        this->btime = btime;
        this->remaining_time = btime;
    }
};

void Request::getInputs(int id)
{
    process_id = id;
    cout << "Enter your name: ";
    cin >> name;

    atime = 0;
    do
    {
        cout << "Enter arrival time (HHMM) between 1000 and 1200: ";
        cin >> atime;
    } while (atime < 1000 || atime > 1200);

    btime = 0;
    do
    {
        cout << "Enter burst time (in minutes): ";
        cin >> btime;
    } while (btime <= 0);

    do
    {
        cout << "Select student (s/S) or teacher (t/T): ";
        cin >> person;
    } while (person != 's' && person != 't' && person != 'S' && person != 'T');

    cout << '\n';
};

class RoundRobin
{
private:
    // time quantum
    int time_slice;
    // student and teacher queues
    queue<Request> qS;
    queue<Request> qT;
    // current time
    int cur;
    char cur_q = '0';
    int total_time;
    int queries;
    int lastChecked = 999;

public:
    RoundRobin(int tq)
    {
        this->time_slice = tq;
        this->cur = 1000;
        this->total_time = 0;
        this->queries = 0;
        this->lastChecked = 1000;
    }

    void addQueue(Request r[], int req, int ct)
    {
        for (int i = 0; i < req; i++)
        {
            if (r[i].atime <= ct && r[i].atime > (lastChecked))
            {
                if (r[i].person == 's' || r[i].person == 'S')
                {
                    qS.push(r[i]);
                }
                else
                {
                    qT.push(r[i]);
                }
            }
        }
        lastChecked = ct;
    }

    void schedule(Request data[], int n)
    {
        int context_switches;
        for (int time = 1000; time < 1200; time += time_slice)
        {
            if (time >= 1060 && time < 1160)
            {
                time = (time + 40);
            }
            else if (time >= 1160 && time < 1200)
            {
                time = 1200;
                break;
            }

            addQueue(data, n, time);
            cout << time << " " << cur_q << endl;
            if (qT.empty() && qS.empty())
            {
                cur_q = '0';
                continue;
            }
            else if (qS.empty())
            {
                cur_q = 't';
            }
            else if (qT.empty())
            {
                cur_q = 's';
            }

            if (cur_q == '0')
            {
                if (!qS.empty() && !qT.empty() && qS.front().atime < qT.front().atime)
                {
                    cur_q = 's';
                }
                else
                {
                    cur_q = 't';
                }
            }
            cout << "\t\t\t\t\t\t " << time << " " << cur_q << endl;

            if (cur_q == 's')
            {
                Request r = qS.front();
                qS.pop();
                context_switches++;
                if (r.remaining_time > time_slice)
                {
                    r.remaining_time = r.remaining_time - time_slice;
                    qS.push(r);
                    total_time += time_slice;
                }
                else
                {
                    total_time += r.remaining_time;
                    time = time - (time_slice - r.remaining_time);
                    cout << "Process " << r.process_id << " completed at " << time << endl;
                    r.remaining_time = 0;
                }
                cur_q = 't';
            }
            else
            {
                Request r = qT.front();
                qT.pop();
                context_switches++;
                if (r.remaining_time > time_slice)
                {
                    r.remaining_time = r.remaining_time - time_slice;
                    qT.push(r);
                    total_time += time_slice;
                }
                else
                {
                    total_time += r.remaining_time;
                    time = time - (time_slice - r.remaining_time);
                    cout << "Process " << r.process_id << " completed at " << time << endl;
                    r.remaining_time = 0;
                }
                cur_q = 's';
            }
        }

        cout << total_time << endl;
        cout << total_time / float(context_switches) << endl;
    }
};

int main()
{
    // Enter time slice
    int tq;
    cout << "Enter time slice for each appointment: ";
    cin >> tq;

    // Ask for number of requests from user
    int requests;
    cout << "Enter number of requests: ";
    cin >> requests;

    // Store data in 2D array
    Request data[requests];

    // Ask user for input
    for (int i = 0; i < requests; i++)
    {
        Request obj;
        obj.getInputs(i + 1);
        data[i] = obj;
    }

    // Create scheduler object
    RoundRobin scheduler(tq);
    scheduler.schedule(data, requests);

    // Display data
    cout << "Process ID: "
         << "      "
         << "Name: "
         << "      "
         << "Arrival Time"
         << "      "
         << "Burst Time: "
         << "      "
         << "Student/Teacher" << '\n';

    for (int i = 0; i < requests; i++)
    {
        cout << data[i].process_id << "      " << data[i].name << "      " << data[i].atime << "      " << data[i].btime << "      " << data[i].person << '\n';
    }

    return 0;
}