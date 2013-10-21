#pragma once

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

/*
* For reduction
*/
class Reduction {
protected:		
	size_t size;
	double value;
	boost::mutex mutex;
	boost::condition_variable cond;

public:
	Reduction() : size(0), value(0) {}
	Reduction(const size_t& sz) : size(sz), value(0) {}
	~Reduction() {}

	void processNewValue(const double& val, const int& num = 1);	
	void changeSize(const int& num);
	double waitForResult();		
};
