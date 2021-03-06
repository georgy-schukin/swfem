#pragma once

#include "irts.h"
#include <vector>
#include <map>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

/**
* Generic program of a fragmented program
* To buid a structure of a program (spawn fragments, etc.)
* and control execution of it
*/
class FragmentedProgram {
private:
	typedef std::map<size_t, ReductionCompFragmentPtrArray> ReductionCFsMap;
	//typedef std::map<size_t, EventCompFragmentPtrArray> EventCFsMap;

private:
	IRuntimeSystem* rts;	// link to runtime system interface for access to its functions

	boost::ptr_list<CompFragment> cfs_storage; // to store created cfs

	//CompFragmentPtrArray new_cfs;	
	ReductionCFsMap reduction_cfs;
	//EventCFsMap event_cfs;
	CompFragmentBunch added_cfs;

	boost::mutex mutex;
	boost::condition_variable cond;

private:
	void deleteDoneCFs();

protected:	
	void addCF(CompFragment* cf, const size_t& group_id = 0, const size_t& priority = 0, const int& node = -1);
	void addReductionCF(ReductionCompFragment* cf, const size_t& red_id, const size_t& group_id = 0, const size_t& priority = 0, const int& node = -1);
	//void addEventCF(const size_t& event_id, EventCompFragment* cf, const size_t& group_id = -1);	

	//void lockDFs(const DataFragmentPtrArray& dfs);
	//void unlockDFs(const DataFragmentPtrArray& dfs);	

	void processCFs();

	double getReductionResult(const size_t& red_id);
	//void waitForEvent(const size_t& event_id);

	int getNodeId();
	int getNumOfNodes();

	void waitForAllDone();

protected:
	IRuntimeSystem* getRTS() const {
		return rts;
	}

public:
	FragmentedProgram(IRuntimeSystem* s) : rts(s) {}
	virtual ~FragmentedProgram() {}	
};
