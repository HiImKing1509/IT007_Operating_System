/*------------------------------------------------------------------------*
|    User: Huynh Viet Tuan Kiet                                           |
|    ID: 20521494														  |
|    Degree: Student - Formal University                                  |
|    Study Computer Science at the University of Information Technology   |
|    Country: Viet Nam                                                    |
|    City: Ho Chi Minh                                                    |
|    Organization: VNUHCM - UIT - University of Information Technology    |
*-------------------------------------------------------------------------*/

/* --------------- Shortest Remaining Time First ---------------*/

#include <bits/stdc++.h>

using namespace std;

#define MIN -1
#define MAX INT_MAX
struct process {
    int id;
    int arr;
    int bur;
    int start;
    int finish;
    int tat;
    int wt;
};

int tottat = 0, totwt = 0;

void SRT() 
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    // Init 1 vector contains n processes (n >= 1)
    vector<process>p(n);

    // Check if the process has been completed or not
    vector<bool>check(n, false);

    // Init 1 vector contains burst remain time of processes
    vector<int>bur_remain(n, 0);

    //Enter Process Name, Arrival Time and Burst Time
    for (int j = 0; j < n; j++)
    {
        cout << "Enter the Process Name, Arrival Time & Burst Time: ";
        cin >> p[j].id >> p[j].arr >> p[j].bur;
    }

    for (int j = 0; j < n; j++) bur_remain[j] = p[j].bur;

    int time_current = 0, count = 0;

    while (count != n)
    {
        //Iterate through all processes to find the one that arrived with the smallest burst remain time
        int i = MIN, new_remain = MAX;
        for (int j = 0; j < n; j++)
        {
            if (p[j].arr <= time_current && !check[j])
            {
                if ((bur_remain[j] < new_remain) || (bur_remain[j] == new_remain && p[j].arr < p[i].arr))
                {
                    new_remain = bur_remain[j];
                    i = j;
                }
            }
        }

        // If i != -1, process found
        if (i != MIN)
        {

            if (bur_remain[i] == p[i].bur) p[i].start = time_current;
            
            bur_remain[i]--;
            time_current++;

            if (bur_remain[i] == 0)
            {
                p[i].finish = time_current;
                p[i].tat = p[i].finish - p[i].arr;
                p[i].wt = p[i].tat - p[i].bur;

                tottat += p[i].tat;
                totwt += p[i].wt;

                check[i] = true;
                count++;
            }
        }
        // If i == 1, no process yet
        else time_current++;
    }

    // Print the result
    cout << "\n\nPName\tArrTime\tBurTime\tStart\tTAT\tFinish\tWaiting\n";

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

    SRT();
    return 0;
}