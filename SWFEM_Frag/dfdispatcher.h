#pragma once

#include "idfdispatcher.h"
#include "idflistener.h"
#include <vector>
#include <boost/thread/mutex.hpp>

class DFDispatcher: public IDFDispatcher {
private:
	//typedef boost::ptr_map<size_t, DataFragment> DataFragments;

private:
	//DataFragments dataFragments;	
	std::vector<IDFListener*> dfListeners;
	boost::mutex mutex;

public:
	DFDispatcher() {}
	~DFDispatcher() {}	

	/*void getReadyDFs(const DataFragmentPtrArray& src, DataFragmentPtrArray& ready_dfs);	
	void getReadyDFsAndLock(const DataFragmentPtrArray& src, DataFragmentPtrArray& ready_dfs);	

	void lockDFs(const DataFragmentPtrArray& dfs);
	void unlockDFs(const DataFragmentPtrArray& dfs);*/

	void addDFListener(IDFListener *l);
};
