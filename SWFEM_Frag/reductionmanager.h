#pragma once

#include "ireductionmanager.h"
#include "icflistener.h"
#include "reduction.h"
#include "icommunicator.h"
#include <boost/ptr_container/ptr_map.hpp>

class ReductionManager : public IReductionManager, public ICFListener {
private:
	typedef boost::ptr_map<size_t, Reduction> ReductionMap;

private:
	ReductionMap reductions;
	ICommunicator *comm;

public:
	ReductionManager(ICommunicator *cm) : comm(cm) {}
	virtual ~ReductionManager() {}

	//void registerReductionCF(size_t red_id, ReductionCompFragment *cf);
	void registerReductionCFs(const size_t& red_id, const ReductionCompFragmentPtrArray& cfs);
	double waitForReductionResult(const size_t& red_id);

	//void onCFDone(CompFragment *cf);
	void onCFsDone(CompFragmentBunch& cf_bunch);
};
