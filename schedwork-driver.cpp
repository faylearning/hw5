// main() program to test your schedule function.
// Feel free to modify this program in any way you need for testing.
// It will not be graded. 
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "schedwork.h"

using namespace std;

void printSchedule(const DailySchedule& sched);

int main()
{
    DailySchedule sched;
    //size_t dailyNeed = 4;
    //size_t maxShifts = 4;
	// bool expectedResult = true;
    AvailabilityMatrix avail = { 
        {1, 0, 1, 0, 1, 1, 0, 1}, // 2, 4, 5, 7
        {1, 0, 1, 0, 0, 1, 1, 0}, // 0, 2, 5, 6 
        {1, 1, 0, 0, 0, 0, 1, 1}, // 0, 1, 6, 7
        {0, 1, 0, 1, 1, 0, 1, 0}, // 1, 3, 4, 6
        {0, 1, 1, 0, 1, 0, 0, 1}, // 1, 2, 4, 7
        {1, 1, 0, 1, 1, 1, 0, 1}, // 0, 2, 3, 5
        {1, 1, 0, 1, 1, 0, 0, 1}  // 0, 3, 4, 7
    };

    bool solutionFound = schedule(avail, 4, 4, sched);
    if(solutionFound)
    {
        cout << "printSchedule" << endl;
        printSchedule(sched);
    }
    else
    {
        cout << "No solution found!" << endl;
    }


    // Replace the matrix below with your test case
    // AvailabilityMatrix avail = { 
    //     {1, 1, 1, 1},
    //     {1, 0, 1, 0},
    //     {1, 1, 0, 1},
    //     {1, 0, 0, 1}
    // };
    // //DailySchedule sched;
    
    // bool solutionFound = schedule(avail, 2, 2, sched);
    // if(solutionFound)
    // {
    //     cout << "printSchedule" << endl;
    //     printSchedule(sched);
    // }
    // else
    // {
    //     cout << "No solution found!" << endl;
    // }
    return 0;
}

void printSchedule(const DailySchedule& sched)
{
    int day = 0;
    for(auto s : sched)
    {
        cout << "Day " << day << ": ";
        for(auto nurse : s)
        {
            cout << nurse << " ";
        }
        cout << endl;
        day++;
    }
}
