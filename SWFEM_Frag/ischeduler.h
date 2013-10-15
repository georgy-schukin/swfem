#pragma once

#include "compfragment.h"
#include <vector>

/**
 * Interface for comp fragment scheduler
 */
class IScheduler {
public:	
	//virtual unsigned int scheduleCF(CompFragment *cf) = 0;
	virtual void scheduleCFs(const CompFragmentPtrArray& cfs, std::vector<unsigned int>& thread_ids) = 0;

	virtual ~IScheduler() {}
};
