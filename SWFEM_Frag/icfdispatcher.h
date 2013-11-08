#pragma once

#include "compfragment.h"
#include "datafragment.h"
#include "reductioncompfragment.h"
#include "compfragmentbunch.h"

/**
* Generic interface for a dispatcher of computational fragments
*/
class ICFDispatcher {
public:
	//virtual void addCF(CompFragment *cf) = 0;	// add new cf on the node		
	//virtual void addCF(CompFragment *cf, const int& node) = 0;
	//virtual void addCFs(const CompFragmentPtrArray& cfs) = 0;	// add new cf on the node	
	virtual void addCFs(CompFragmentBunch& cfs) = 0;	// add new cf on the node	
	//virtual void addReductionCF(const size_t& red_id, ReductionCompFragment* cf, const int& node = -1) = 0;	
	virtual void waitForAllDone() = 0;	

	//virtual void lockDFs(const DataFragmentPtrArray& dfs) = 0;
	//virtual void unlockDFs(const DataFragmentPtrArray& dfs) = 0;	

	virtual ~ICFDispatcher() {}
};
