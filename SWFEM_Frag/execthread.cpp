#include "execthread.h"
#include "timer.h"
#include "mpelogger.h"
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <sstream>

ExecThread::ExecThread(const size_t& t_id, const int& node) : thread_id(t_id), this_node(node), is_working(true) {	
	thread = boost::thread(boost::bind(&ExecThread::threadFunc, this));	// start thread
}

ExecThread::~ExecThread() {
	is_working.store(false);
	cond.notify_all();
	thread.join();
}

/*void ExecThread::execCFs(const CompFragmentPtrArray& cfs) {
	boost::unique_lock<boost::mutex> lock(mutex);
	cfs_queue.insert(cfs_queue.end(), cfs.begin(), cfs.end());
	cond.notify_one();
}*/

void ExecThread::execCFs(const CompFragmentBunch& cf_bunch) {
	boost::unique_lock<boost::mutex> lock(mutex);
	exec_queue.push(boost::shared_ptr<CompFragmentBunch>(new CompFragmentBunch(cf_bunch)));
	cond.notify_one();
}

void ExecThread::threadFunc() {
	double tw = 0, ts = 0;
	size_t cnt = 0;

	Timer timer;
	MPELogger mpe_logger;

	MPELogger::MPEEvent compute_event = mpe_logger.newEvent("Compute", "red");

	while(is_working.load()) {		
		boost::unique_lock<boost::mutex> lock(mutex);			
		if (!exec_queue.empty()) {
			boost::shared_ptr<CompFragmentBunch> cf_bunch_ptr(exec_queue.front());
			CompFragmentBunch& cf_bunch = *(cf_bunch_ptr.get());						
			exec_queue.pop();
			lock.unlock();

			BOOST_FOREACH(CompFragment *cf, cf_bunch)
				cf->execute();

			BOOST_FOREACH(ICFListener *listener, cf_listeners)
				listener->onCFsDone(cf_bunch);

			cnt += cf_bunch.size();
		} else {
			cond.timed_wait(lock, boost::posix_time::seconds(1)); // wait for next cfs or just for 1 second
		}
	}
	std::ostringstream out;
	out << this_node << " : Thread " << thread_id << " : Work " << tw << " System " << ts << " [" << cnt << "]" << std::endl; 
	std::cout << out.str();
}

void ExecThread::addCFListener(ICFListener *listener) {
	cf_listeners.push_back(listener);
}

