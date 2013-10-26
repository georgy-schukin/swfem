#pragma once

#include "reductioncompfragment.h"

/**
 * Interface for manager for reduction comp fragments
 */
class IReductionManager {
public:
	//virtual void registerReductionCF(const size_t& red_id, ReductionCompFragment *cf) = 0;
	virtual void registerReductionCFs(const size_t& red_id, const ReductionCompFragmentPtrArray& cfs) = 0;	
	virtual double waitForReductionResult(const size_t& red_id) = 0;

	virtual ~IReductionManager() {}
};
