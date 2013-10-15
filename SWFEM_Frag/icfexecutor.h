#pragma once

#include "compfragment.h"
#include "icflistener.h"

/**
 * Interface for comp fragment executor
 */
class ICFExecutor {
public:
	//virtual void execCF(CompFragment* cf) = 0;
	virtual void execCFs(const CompFragmentPtrArray& cfs) = 0;
	virtual void addCFListener(ICFListener *l) = 0;	

	virtual ~ICFExecutor() {}
};