/*------------------------------------------------------------------------*
|    User: Huynh Viet Tuan Kiet                                           |
|    ID: 20521494							  |
|    Degree: Student - Formal University                                  |
|    Study Computer Science at the University of Information Technology   |
|    Country: Viet Nam                                                    |
|    City: Ho Chi Minh                                                    |
|    Organization: VNUHCM - UIT - University of Information Technology    |
*-------------------------------------------------------------------------*/

/* --------------- Page Replacement Algorithm ---------------*/


#include <bits/stdc++.h>
#include <unordered_set>


using namespace std;

void Format_code(int num)
{
    for (int i = 0; i < 2 * num; i++) cout << "-";
    cout << "\n";
}

bool Find_FIFO(vector<int>& a, int num)
{
    if (find(a.begin(), a.end(), num) != a.end()) return true;
    else return false;
}

int Find_LRU(vector<pair<int, int>>& a, int num)
{
    for (int i = 0; i < a.size(); i++)
        if (a[i].first == num)
            return i;
    return -1;
}

int Find_OPT(vector<int>& a, int num)
{
    for (int i = 0; i < a.size(); i++)
        if (a[i] == num)
            return i;
    return -1;
}

void FIFO(int page_num, vector<int>& p, int frame)
{
    cout << "\t";
    Format_code(page_num);
    cout << "\tFirst in First out\n";
    vector<int>page(p);
    cout << "\t";
    Format_code(page_num);
    cout << "Page:\t";
    for (int i = 0; i < page_num; i++) cout << page[i] << " ";
    // Đếm số lượng lỗi trang
    vector<char>page_fault(page_num, ' ');

    // Chứa các trang đang nằm trong Frame
    vector<int>FRAME;

    // Ma trận kết quả
    vector<vector<string>> matrix_result(frame, vector<string>(page_num, " "));
    int prior = 0;
    for (int i = 0; i < page_num; i++)
    {
        if (Find_FIFO(FRAME, page[i])) {}
        else
        {
            if (FRAME.size() < frame) FRAME.push_back(page[i]);
            else
            {
                swap(FRAME[prior], page[i]);
                prior++;
                if (prior == frame) prior = 0;
            }
            page_fault[i] = '*';
        }
        for (int row = 0; row < FRAME.size(); row++)
            matrix_result[row][i] = to_string(FRAME[row]);
    }
    cout << "\n\t";
    for (int r = 0; r < frame; r++)
    {
        for (int c = 0; c < page_num; c++)
        {
            cout << matrix_result[r][c] << " ";
        }
        cout << "\n\t";
    }
    Format_code(page_num);
    cout << "\t";
    for (int i = 0; i < page_num; i++) cout << page_fault[i] << " ";
    cout << "\nNumber of Page Fault: " << count(page_fault.begin(), page_fault.end(), '*') << "\n";
}
void LRU(int page_num, vector<int>& p, int frame)
{
    cout << "\t";
    Format_code(page_num);
    cout << "\tLeast Recent Used\n";
    vector<pair<int,int>>page(page_num);
    for (int i = 0; i < page_num; i++)
    {
        page[i].first = p[i];
        page[i].second = i;
    }
    cout << "\t";
    Format_code(page_num);
    cout << "Page:\t";
    for (int i = 0; i < page_num; i++) cout << page[i].first << " ";
    
    // Đếm số lượng lỗi trang
    vector<char>page_fault(page_num, ' ');

    // Chứa các trang đang nằm trong Frame
    vector<pair<int,int>>FRAME;

    // Ma trận kết quả
    vector<vector<string>> matrix_result(frame, vector<string>(page_num, " "));

    for (int i = 0; i < page.size(); i++)
    {
        int find = Find_LRU(FRAME, page[i].first);
        if (find != -1) swap(FRAME[find], page[i]);
        else
        {
            if (FRAME.size() < frame) FRAME.push_back(page[i]);
            else
            {
                int vtj = -1;
                int lc = INT_MAX;
                for (int j = 0; j < FRAME.size(); j++)
                {
                    if (FRAME[j].second < lc)
                    {
                        lc = FRAME[j].second;
                        vtj = j;
                    }
                }
                swap(FRAME[vtj], page[i]);
            }
            page_fault[i] = '*';
        }
        for (int row = 0; row < FRAME.size(); row++)
            matrix_result[row][i] = to_string(FRAME[row].first);
    }
    cout << "\n\t";
    for (int r = 0; r < frame; r++)
    {
        for (int c = 0; c < page_num; c++)
        {
            cout << matrix_result[r][c] << " ";
        }
        cout << "\n\t";
    }
    Format_code(page_num);
    cout << "\t";
    for (int i = 0; i < page_num; i++) cout << page_fault[i] << " ";
    cout << "\nNumber of Page Fault: " << count(page_fault.begin(), page_fault.end(), '*') << "\n";
}

void OPT(int page_num, vector<int>&p, int frame)
{
    cout << "\t";
    Format_code(page_num);
    cout << "\tOptimal\n";
    vector<int>page(p);
    cout << "\t";
    Format_code(page_num);
    cout << "Page:\t";
    for (int i = 0; i < page_num; i++) cout << page[i] << " ";
    // Đếm số lượng lỗi trang
    vector<char>page_fault(page_num, ' ');

    // Chứa các trang đang nằm trong Frame
    vector<int>FRAME;

    // Ma trận kết quả
    vector<vector<string>> matrix_result(frame, vector<string>(page_num, " "));
    for (int i = 0; i < page_num; i++)
    {
        if (Find_OPT(FRAME, page[i]) != -1) {}
        else
        {
            if (FRAME.size() < frame) FRAME.push_back(page[i]);
            else
            {

                vector<int>vec(frame, -1);
                int order = 0;
                int prior = -1;
                for (int j = i + 1; j < page_num; j++)
                {
                    int vt = Find_OPT(FRAME, page[j]);
                    if (vt != -1)
                    {
                        if (vec[vt] == -1)
                        {
                            vec[vt] = order;
                            prior = vt;
                            order++;
                        }
                    }
                }
                if (order == frame) {}
                else
                {
                    for (int j = 0; j < vec.size(); j++)
                    {
                        if (vec[j] == -1)
                        {
                            prior = j;
                            break;
                        }
                    }
                }
                swap(FRAME[prior], page[i]);
            }
            page_fault[i] = '*';
        }
        for (int row = 0; row < FRAME.size(); row++)
            matrix_result[row][i] = to_string(FRAME[row]);
    }
    cout << "\n\t";
    for (int r = 0; r < frame; r++)
    {
        for (int c = 0; c < page_num; c++)
        {
            cout << matrix_result[r][c] << " ";
        }
        cout << "\n\t";
    }
    Format_code(page_num);
    cout << "\t";
    for (int i = 0; i < page_num; i++) cout << page_fault[i] << " ";
    cout << "\nNumber of Page Fault: " << count(page_fault.begin(), page_fault.end(), '*') << "\n";
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int page_number, frame_number;
    cout << "Enter page number: "; cin >> page_number;
    vector<int>Input(page_number);
    cout << "Manual input sequence: ";
    for (int i = 0; i < page_number; i++)
        cin >> Input[i];
    cout << "Input page frames: "; cin >> frame_number;

	bool flag = true;
	do
	{
		//system("cls");
        cout << "\n--- Page Replacement algorithm ---\n";
		int n;
        cout << "\n0. Exit";
        cout << "\n1. FIFO algorithm";
        cout << "\n2. OPT algorithm";
        cout << "\n3. LRU algorithm";
        cout << "\n--> Algorithm selection or Exit (0 -> 3): ";

		cin >> n;
		switch (n)
		{
		case 1:
        {
            FIFO(page_number, Input, frame_number);
            break;
        }
        case 2:
        {
            OPT(page_number, Input, frame_number);
            break;
        }
        case 3:
        {
            LRU(page_number, Input, frame_number);
            break;
        }
        case 0:
        {
            flag = false;
            cout << "\n";
            break;
        }
		default:
			cout << "\nInvalid, try again!!!";
			cout << "\n";
			break;
		}
		system("pause");
	} while (flag);
    return 0;
}
