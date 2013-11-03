#pragma once

#include "compfragment.h"
#include "compfragmentbunch.h"
#include "compfragmentgroup.h"

/**
 * Interface for comp fragment scheduler
 */
class ICFScheduler {
public:	
	//virtual void scheduleCF(CompFragment *cf) = 0;
	//virtual void scheduleCFs(CompFragmentPtrArray& cfs) = 0;
	virtual void scheduleCFs(const CompFragmentBunch& cf_bunch) = 0;
	//virtual void scheduleCFGroup(const CompFragmentGroup& cf_group) = 0;
	//virtual size_t scheduleCF(CompFragment *cf) = 0;
	//virtual void scheduleCFs(const CompFragmentPtrArray& cfs, std::vector<size_t>& thread_ids) = 0;

	virtual ~ICFScheduler() {}
};
