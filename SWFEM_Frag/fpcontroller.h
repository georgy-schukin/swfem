#pragma once

#include "irts.h"
#include <vector>
#include <map>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

/**
* Generic controller of a fragmented program
* To buid a structure of a program (spawn fragments, etc.)
* and control execution of it
*/
class FPController {
private:
	typedef std::map<unsigned int, ReductionCompFragmentPtrArray> ReductionCFsMap;
	//typedef std::map<unsigned int, EventCompFragmentPtrArray> EventCFsMap;

private:
	IRuntimeSystem* rts;	// link to runtime system interface for access to its functions

	boost::ptr_list<CompFragment> cfs_storage; // to store created cfs

	CompFragmentPtrArray new_cfs;	
	ReductionCFsMap reduction_cfs;
	//EventCFsMap event_cfs;

	boost::mutex mutex;
	boost::condition_variable cond;

private:
	void deleteDoneCFs();

protected:	
	void addCF(CompFragment* cf, const int& node = -1);			
	void addReductionCF(const unsigned int& red_id, ReductionCompFragment* cf, const int& node = -1);
	//void addEventCF(const unsigned int& event_id, EventCompFragment* cf, const unsigned int& group_id = -1);	

	//void lockDFs(const DataFragmentPtrArray& dfs);
	//void unlockDFs(const DataFragmentPtrArray& dfs);	

	void processCFs();

	double getReductionResult(const unsigned int& red_id);
	//void waitForEvent(const unsigned int& event_id);

	int getNodeId();
	int getNodesNum();

	void waitForAllDone();

protected:
	IRuntimeSystem* getRTS() const {
		return rts;
	}

public:
	FPController(IRuntimeSystem* s) : rts(s) {}
	virtual ~FPController() {}	
};
