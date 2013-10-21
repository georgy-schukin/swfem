#pragma once

#include "compfragment.h"
#include <vector>

/**
 * Interface for comp fragment scheduler
 */
class IScheduler {
public:	
	//virtual size_t scheduleCF(CompFragment *cf) = 0;
	virtual void scheduleCFs(const CompFragmentPtrArray& cfs, std::vector<size_t>& thread_ids) = 0;

	virtual ~IScheduler() {}
};
