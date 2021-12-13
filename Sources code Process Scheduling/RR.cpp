/*------------------------------------------------------------------------*
|    User: Huynh Viet Tuan Kiet                                           |
|    ID: 20521494														  |
|    Degree: Student - Formal University                                  |
|    Study Computer Science at the University of Information Technology   |
|    Country: Viet Nam                                                    |
|    City: Ho Chi Minh                                                    |
|    Organization: VNUHCM - UIT - University of Information Technology    |
*-------------------------------------------------------------------------*/

/* --------------- Round Robin ---------------*/

#include <bits/stdc++.h>

using namespace std;

struct Process
{
    int id; //Process Name
    int arr; //Arrival Time
    int bur; // Burst Time
    int start; // Start Time
    int finish; // Finish time
    int wt; // Waiting Time
    int tat; // Turnaround Time
};

int tottat = 0, totwt = 0;
void swap(Process& p1, Process& p2)
{
    Process temp = p1;
    p1 = p2;
    p2 = temp;
}

void Sort_Arrival_Time(vector<Process>& a, int n)
{
    if (n == 1) return;
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i].arr > a[i + 1].arr)
            swap(a[i], a[i + 1]);
    }
    Sort_Arrival_Time(a, n - 1);
}
void Sort_ID(vector<Process>& a, int n)
{
    if (n == 1) return;
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i].id > a[i + 1].id)
            swap(a[i], a[i + 1]);
    }
    Sort_ID(a, n - 1);
}

void RR()
{
    int n;
    cout << "Enter the number of Processes: "; cin >> n;

    int time_slice;
    cout << "Enter Quantum time: "; cin >> time_slice;

    int time_current = 0, count = 0, i = 0;

    // Init 1 vector contains n processes (n >= 1)
    vector<Process>p(n);

    // Init 1 vector contains burst remain time of processes
    vector<int>bur_remain(n, 0);

    // Check if the process has entered the queue or not
    vector<bool>check(n, false);
    check[0] = true;

    // Queue contains processes waiting to execute
    queue<int>que;
    que.push(0);

    //Enter Process Name, Arrival Time and Burst Time
    for (int j = 0; j < n; j++)
    {
        cout << "Enter the Process Name, Arrival Time & Burst Time: ";
        cin >> p[j].id >> p[j].arr >> p[j].bur;
    }
    Sort_Arrival_Time(p, n);
    
    for (int j = 0; j < n; j++)
        bur_remain[j] = p[j].bur;

    while (count < n)
    {
        // Take the first Process from the queue to execute
        i = que.front();

        // Remove the first Process from the queue
        que.pop();

        // If the process has burst remain time = burst time => Execution for the first time 
        if (bur_remain[i] == p[i].bur)
        {
            p[i].start = max(time_current, p[i].arr);
            time_current = p[i].start;
        }

        // If the process has burst remain time <= time slice => process completed
        if (bur_remain[i] <= time_slice)
        {
            time_current += bur_remain[i];
            bur_remain[i] = 0;
            p[i].finish = time_current;
            p[i].tat = p[i].finish - p[i].arr;
            p[i].wt = p[i].tat - p[i].bur;
            tottat += p[i].tat;
            totwt += p[i].wt;
            count++;
        }
        else
        {
            bur_remain[i] -= time_slice;
            time_current += time_slice;
        }

        // Check for processes that are out of the queue
        for (int j = 1; j < n; j++)
        {
            if (p[j].arr <= time_current && bur_remain[j] > 0 && !check[j])
            {
                que.push(j);
                check[j] = true;
            }
        }

        // If the process has just finished executing and still has a burst time, add it to the end of the queue
        if (bur_remain[i] > 0) que.push(i);

        // If the queue is empty and all progress is not completed yet => The remaining processes have arrival time > current time
        if (que.size() == 0)
        {
            for (int j = 1; j < n; j++)
            {
                if (bur_remain[j] > 0)
                {
                    que.push(j);
                    check[j] = true;
                    break;
                }
            }
        }
    }

    // Print the result
    Sort_ID(p, n);
    cout << "\nPName\tArrTime\tBurTime\tStart\tTAT\tFinish\tWaiting\n";

    for (int j = 0; j < n; j++)
    {
        cout << "P" << p[j].id << "\t";
        cout << p[j].arr << "\t";
        cout << p[j].bur << "\t";
        cout << p[j].start << "\t";
        cout << p[j].tat << "\t";
        cout << p[j].finish << "\t";
        cout << p[j].wt << "\n";
    }
    cout << "\nAverage Waiting Time: " << (float)totwt / n << " (ms)";
    cout << "\nAverage Turnaround Time: " << (float)tottat / n << " (ms)";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    RR();
    return 0;
}