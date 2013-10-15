#pragma once

#include "datafragment.h"
#include "idflistener.h"

/**
* Generic interface for a dispatcher of data fragments
*/
class IDFDispatcher {
public:
	virtual void getReadyDFs(const DataFragmentPtrArray& src, DataFragmentPtrArray& ready_dfs) = 0;	
	virtual void getReadyDFsAndLock(const DataFragmentPtrArray& src, DataFragmentPtrArray& ready_dfs) = 0;	

	virtual void lockDFs(const DataFragmentPtrArray& dfs) = 0;
	virtual void unlockDFs(const DataFragmentPtrArray& dfs) = 0;	

	virtual void addDFListener(IDFListener *l) = 0;	

	virtual ~IDFDispatcher() {}
};
