#include "reduction.h"

void Reduction::processNewValue(const double& val, const int& num) {
	boost::unique_lock<boost::mutex> lock(mutex);	
	if (value < val) value = val; // get max	
	size -= num;
	if (size == 0) 
		cond.notify_one();
}

double Reduction::waitForResult() {
	boost::unique_lock<boost::mutex> lock(mutex);
	while(size > 0) 
		cond.wait(lock);	// wait until all local reductions are done
	return value;
}

void Reduction::changeSize(const int& num) {
	boost::unique_lock<boost::mutex> lock(mutex);	
	size += num;
}

