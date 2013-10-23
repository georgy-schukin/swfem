#pragma once

#include "compfragment.h"
#include "compfragmentgroup.h"
#include "icflistener.h"

/**
* Interface for fragment execution subsystem
*/
class IThreadPool {
public:
	//virtual void execCF(CompFragment *cf, const size_t& thread_id) = 0;	// place fragment for execution	
	//virtual void execCFs(const CompFragmentPtrArray& cfs, const size_t& thread_id) = 0;	// place fragments for execution on specified thread	
	virtual void execCFGroup(const CompFragmentGroup& group, const size_t& thread_id) = 0;

	virtual size_t getNumOfThreads() const = 0;

	virtual void addCFListener(ICFListener *l) = 0;

	virtual ~IThreadPool() {}
};
