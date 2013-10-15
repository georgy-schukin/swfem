#pragma once

#include "compfragment.h"
#include "icflistener.h"

/**
* Interface for fragment execution subsystem
*/
class IThreadPool {
public:
	//virtual void execCF(CompFragment *cf, unsigned int thread_id) = 0;	// place fragment for execution	
	virtual void execCFs(const CompFragmentPtrArray& cfs, const unsigned int& thread_id) = 0;	// place fragments for execution on specified thread
	virtual void addCFListener(ICFListener *l) = 0;

	virtual ~IThreadPool() {}
};
