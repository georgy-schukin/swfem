#pragma once

#include "reductioncompfragment.h"

/**
 * Interface for manager for reduction comp fragments
 */
class IReductionManager {
public:
	virtual void registerReductionCF(const unsigned int& red_id, ReductionCompFragment *cf) = 0;
	virtual void registerReductionCFs(const unsigned int& red_id, const ReductionCompFragmentPtrArray& cfs) = 0;	
	virtual double waitForReductionResult(const unsigned int& red_id) = 0;

	virtual ~IReductionManager() {}
};
