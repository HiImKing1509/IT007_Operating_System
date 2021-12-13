/*------------------------------------------------------------------------*
|    User: Huynh Viet Tuan Kiet                                           |
|    ID: 20521494														  |
|    Degree: Student - Formal University                                  |
|    Study Computer Science at the University of Information Technology   |
|    Country: Viet Nam                                                    |
|    City: Ho Chi Minh                                                    |
|    Organization: VNUHCM - UIT - University of Information Technology    |
*-------------------------------------------------------------------------*/

/* --------------- First Come First Serve ---------------*/

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

int totwt = 0, tottat = 0;

void swap(Process& p1, Process& p2)
{
    Process temp = p1;
    p1 = p2;
    p2 = temp;
}

void Sort(vector<Process>& a, int n)
{
    if (n == 1) return;
    for (int i = 0; i < n - 1; i++)
    {
        if ((a[i].arr > a[i + 1].arr) || (a[i].arr == a[i + 1].arr && a[i].bur > a[i + 1].bur))
            swap(a[i], a[i + 1]);
    }
    Sort(a, n - 1);
}

void FCFS()
{
    int n;
    cout << "Enter the number of Processes: "; cin >> n;

    //Init 1 vector contains n processes (n >= 1)
    vector<Process>p(n);

    //Enter Process Name, Arrival Time and Burst Time
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the Process Name, Arrival Time & Burst Time: ";
        cin >> p[i].id >> p[i].arr >> p[i].bur;
    }

    // Sort processes in ascending Arrival Time
    Sort(p, n);

    // Handling
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            p[i].start = p[i].arr;
            p[i].finish = p[i].start + p[i].bur;
            p[i].wt = 0;
            p[i].tat = p[i].bur;
            totwt += p[i].wt;
            tottat += p[i].tat;
        }
        else
        {
            if (p[i].arr <= p[i - 1].finish) p[i].start = p[i - 1].finish;
            else p[i].start = p[i].arr;

            p[i].finish = p[i].start + p[i].bur;
            p[i].wt = p[i].start - p[i].arr;
            p[i].tat = p[i].finish - p[i].arr;
            totwt += p[i].wt;
            tottat += p[i].tat;
        }
    }

    // Print the result
    cout << "\nPName\tArrTime\tBurTime\tStart\tTAT\tFinish\n";

    for (int i = 0; i < n; i++)
    {
        cout << "P" << p[i].id << "\t";
        cout << p[i].arr << "\t";
        cout << p[i].bur << "\t";
        cout << p[i].start << "\t";
        cout << p[i].tat << "\t";
        cout << p[i].finish << "\n";
    }
    cout << "\nAverage Waiting Time: " << (float)totwt / n << " (ms)";
    cout << "\nAverage Turnaround Time: " << (float)tottat / n << " (ms)";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    FCFS();
    return 0;
}