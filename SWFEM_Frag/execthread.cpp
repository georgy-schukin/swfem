#include "execthread.h"
#include "timer.h"
#include "mpelogger.h"
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <sstream>

ExecThread::ExecThread(const unsigned int& t_id, const int& rnk) : thread_id(t_id), rank(rnk), is_working(true) {	
	thread = boost::thread(boost::bind(&ExecThread::threadFunc, this));	// start thread
}

ExecThread::~ExecThread() {
	is_working.store(false);
	cond.notify_all();
	thread.join();
}

void ExecThread::execCFs(const CompFragmentPtrArray& cfs) {
	boost::unique_lock<boost::mutex> lock(mutex);
	cfs_queue.insert(cfs_queue.end(), cfs.begin(), cfs.end());
	cond.notify_one();
}

void ExecThread::addCFListener(ICFListener *l) {
	cfListeners.push_back(l);
}

void ExecThread::threadFunc() {
	double tw = 0, ts = 0;
	unsigned int cnt = 0;

	Timer timer;
	MPELogger mpe_logger;

	MPELogger::MPEEvent compute_event = mpe_logger.newEvent("Compute", "red");

	while(is_working.load()) {		
		boost::unique_lock<boost::mutex> lock(mutex);
		if(!cfs_queue.empty()) {
			CompFragmentPtrArray cfs(cfs_queue.begin(), cfs_queue.end());			
			cfs_queue.clear();
			lock.unlock();

			mpe_logger.logStart(compute_event);
			timer.start();
			BOOST_FOREACH(CompFragment *cf, cfs) 				
				cf->execute();	
			tw += timer.stop();
			mpe_logger.logEnd(compute_event);

			/*ostringstream out;
			out << "Thread " << thread_id << " : done " << cfs.size() << endl;
			cout << out.str();*/

			timer.start();
			BOOST_FOREACH(ICFListener *l, cfListeners) 
				l->onCFsDone(cfs);			
			ts += timer.stop();

			cnt += cfs.size();			
		} else {
			cond.timed_wait(lock, boost::posix_time::seconds(1)); // wait for next cfs or just for 1 second
		}
	}
	std::ostringstream out;
	out << rank << " : Thread " << thread_id << " : Work " << tw << " System " << ts << " [" << cnt << "]" << std::endl; 
	std::cout << out.str();
}
