#pragma once

//#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/chrono.hpp>

class Timer {
private:
	boost::chrono::high_resolution_clock::time_point beg_time;
	boost::chrono::high_resolution_clock::time_point end_time;
	//boost::posix_time::ptime beg_time;
	//boost::posix_time::ptime end_time;

public:
	Timer() {}
	~Timer() {}

	void start() {		
		//beg_time = boost::posix_time::microsec_clock::universal_time();
		beg_time = boost::chrono::high_resolution_clock::now();
	}	

	double stop() {		
		//boost::posix_time::time_period p(beg_time, end_time);
		//return double(p.length().total_microseconds())/1000000.0;		
		end_time = boost::chrono::high_resolution_clock::now();
		boost::chrono::microseconds ms = boost::chrono::duration_cast<boost::chrono::microseconds>(end_time - beg_time);
		return ((double)ms.count())/1000000.0;
	}
};
