/*------------------------------------------------------------------------*
|    User: Huynh Viet Tuan Kiet                                           |
|    ID: 20521494														  |
|    Degree: Student - Formal University                                  |
|    Study Computer Science at the University of Information Technology   |
|    Country: Viet Nam                                                    |
|    City: Ho Chi Minh                                                    |
|    Organization: VNUHCM - UIT - University of Information Technology    |
*-------------------------------------------------------------------------*/

/* --------------- Shortest Job First ---------------*/  

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
        if ((a[i].arr < a[i + 1].arr) || (a[i].arr == a[i + 1].arr && a[i].bur < a[i + 1].bur))
            swap(a[i], a[i + 1]);
    }
    Sort(a, n - 1);
}

void SJF()
{
    int n;
    cout << "Enter the number of Processes: "; cin >> n;
    //Init 1 vector contains n processes (n >= 1)
    vector<Process>p(n);
    queue<Process>que;

    //Enter Process Name, Arrival Time and Burst Time
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the Process Name, Arrival Time & Burst Time: ";
        cin >> p[i].id >> p[i].arr >> p[i].bur;
    }
    // Sort processes in ascending Arrival Time
    Sort(p, n);
    int time_current = 0;
    // Handling
    for (int i = n - 1; i >= 0; i--)
    {
        if (i == n - 1)
        {
            p[i].start = p[i].arr;
            p[i].finish = p[i].start + p[i].bur;
            time_current = p[i].finish;
            p[i].wt = 0;
            p[i].tat = p[i].bur;
            totwt += p[i].wt;
            tottat += p[i].tat;
            que.push(p[i]);
        }
        else
        {
            int vtj = p.size() - 1;
            bool flag = false;
            int bur_min = p.back().bur;
            for (int j = p.size() - 2; j >= 0; j--)
            {
                if (p[j].bur < bur_min && p[j].arr <= time_current)
                {
                    vtj = j;
                    bur_min = p[j].bur;
                    flag = true;
                }
            }
            if (flag)
            {
                swap(p[vtj], p.back());
                p[i].start = time_current;
            }
            else
            {
                if (p.back().arr <= time_current) p[i].start = time_current;
                else p[i].start = p.back().arr;
            }
            p[i].finish = p[i].start + p[i].bur;
            time_current = p[i].finish;
            p[i].wt = p[i].start - p[i].arr;
            p[i].tat = p[i].finish - p[i].arr;
            totwt += p[i].wt;
            tottat += p[i].tat;
            que.push(p[i]);
        }
        p.pop_back();
    }

    // Print the result
    cout << "\nPName\tArrTime\tBurTime\tStart\tTAT\tFinish\n";

    for (int i = que.size(); i > 0; i--)
    {
        cout << "P" << que.front().id << "\t";
        cout << que.front().arr << "\t";
        cout << que.front().bur << "\t";
        cout << que.front().start << "\t";
        cout << que.front().tat << "\t";
        cout << que.front().finish << "\n";
        que.pop();
    }
    cout << "\nAverage Waiting Time: " << (float)totwt / n << " (ms)";
    cout << "\nAverage Turnaround Time: " << (float)tottat / n << " (ms)";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    SJF();
    return 0;
}