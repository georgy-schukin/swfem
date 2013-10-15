#include "event.h"
#include <iostream>

using namespace std;

void Event::waitForEvent() {
	boost::unique_lock<boost::mutex> lock(mutex);	
	while(size > 0)
		cond.wait(lock);			
}

void Event::changeSize(const int& num) {
	boost::unique_lock<boost::mutex> lock(mutex);
	size += num;
	//cout << "Size " << size << endl;
	if(size == 0) 
		cond.notify_one();
}
