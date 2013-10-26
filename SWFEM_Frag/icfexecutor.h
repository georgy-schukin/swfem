#pragma once

#include "compfragment.h"
#include "compfragmentgroup.h"
#include "icflistener.h"

/**
 * Interface for comp fragment executor
 */
class ICFExecutor {
public:
	//virtual void execCF(CompFragment* cf) = 0;
	//virtual void execCFs(const CompFragmentPtrArray& cfs) = 0;
	virtual void execCFs(const CompFragmentBunch& cf_bunch) = 0;
	virtual void addCFListener(ICFListener *listener) = 0;	

	virtual ~ICFExecutor() {}
};