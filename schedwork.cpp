#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

//n x k vector of vector matrix avail
//int dailyNeed
//int maxShifts 
//vector sched


bool schedRecurse(Worker_T totWorkers, int currDay, size_t currNeed, DailySchedule& sched, 
                  const AvailabilityMatrix& avail, vector<size_t>& shiftsWorked, 
                  const size_t maxShifts, const size_t dailyNeed){
    
    int totDays = sched.size();
    if (currDay == totDays){ 
        return true;
    }

    for (Worker_T currWorker = 0; currWorker < totWorkers; currWorker++){
        if (currNeed >= dailyNeed){
            break;
        }

        bool worked = false;
        for ( size_t d=0; d < dailyNeed; d++){
            if ( sched[currDay][d] == currWorker ){
                worked = true;
                break;
            }
        }
        if (worked) continue;

        if ((avail[currDay][currWorker] != true) || (shiftsWorked[currWorker] >= maxShifts)){
            continue;
        }

        sched[currDay][currNeed] = currWorker;
        shiftsWorked[currWorker]++;

        size_t nextDay = currDay;
        size_t nextNeed = currNeed;
        if ( nextNeed + 1 == dailyNeed){
            nextDay = currDay + 1;
            nextNeed = 0;
        }else
            nextNeed ++;

        bool ret = schedRecurse(totWorkers, nextDay, nextNeed, sched, avail, shiftsWorked, maxShifts, dailyNeed);

        if (ret == true){
            return true;
        }
        shiftsWorked[currWorker]--;
    }
    sched[currDay][currNeed] = INVALID_ID;
    return false;

}

    

    




    //loop through each spot & try worker
    
    // for (Worker_T currWorker = 0; currWorker < totWorkers; currWorker++){
    //     if (currNeed >= dailyNeed){
    //         break;
    //     }

    //     if ((avail[currDay][currWorker] == true) && (shiftsWorked[currWorker] < maxShifts)){
    //         sched[currDay][currNeed] = currWorker;
    //         currNeed++;
    //         shiftsWorked[currWorker]++;
    //     }
    // }

    // if (currNeed < dailyNeed){
    //     return false;
    // }

    // //recurse 
    // bool ret = schedRecurse(totWorkers, ++currDay, sched, avail, shiftsWorked, maxShifts, dailyNeed);

    // if (ret == true){
    //     return true;
    // }






// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
){
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    size_t totWorkers = avail[0].size();
    vector<size_t> shiftsWorked( totWorkers, 0);

    // sched.resize(k);
    for (size_t d = 0; d < avail.size(); d++){
        vector<Worker_T> schedRow;
        for (size_t n = 0; n < dailyNeed; n++){
            schedRow.push_back(INVALID_ID);
        }
        sched.push_back(schedRow);
    }

    return schedRecurse(totWorkers, 0, 0, sched, avail, shiftsWorked, maxShifts, dailyNeed);

}

