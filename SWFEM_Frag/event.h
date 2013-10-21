#pragma once

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

/**
 * Some event to wait for
 */
class Event {
protected:
	size_t size;	// num of steps to complete event
	boost::mutex mutex;
	boost::condition_variable cond;

public:
	Event() : size(0) {}
	Event(const size_t& sz) : size(sz) {}
	~Event() {}

	void changeSize(const int& num);	
	void waitForEvent();
};
