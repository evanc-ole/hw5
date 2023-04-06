#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool sched_recurse(int n, const AvailabilityMatrix& avail, vector<int>& shifts, vector<bool> taken, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched){
	//finished every day
	if(n / sched.size() >= dailyNeed){
		return true;
	}
	int row = n/dailyNeed; int col = n%dailyNeed;
	
	//first column of each day
	if(!col){
		taken.clear();
		taken = vector<bool>(avail[0].size());
	}

	//recurse for every available worker on each day
	for(Worker_T i = 0; i < avail[row].size(); i++){
		if(avail[row][i] && shifts[i] < maxShifts && !taken[i]){
			++shifts[i];
			sched[row][col] = i;
			taken[i] = true;
			if(sched_recurse(n+1, avail, shifts, taken, dailyNeed, maxShifts, sched)){
				return true;
			}
			else{
				--shifts[i];
				sched[row][col] = 0;
				taken[i] = false;
			} 
		}
	}
	return false;
}




// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
	for(size_t i = 0; i < avail.size(); i++){
		vector<Worker_T> temp;
		for(size_t j = 0; j < dailyNeed; j++){
			temp.push_back(0);
		}
		sched.push_back(temp);
	}
	vector<int> shifts(avail[0].size());
	vector<bool> taken(avail[0].size());
	int n = 0;
	bool ret = sched_recurse(n, avail, shifts, taken, dailyNeed, maxShifts, sched);

	return ret;
}

