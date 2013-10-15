#pragma once

#include "ireductionmanager.h"
#include "icflistener.h"
#include "reduction.h"
#include "icommunicator.h"
#include <boost/ptr_container/ptr_map.hpp>

class ReductionManager : public IReductionManager, public ICFListener {
private:
	typedef boost::ptr_map<unsigned int, Reduction> ReductionsMap;

private:
	ReductionsMap reductions;
	ICommunicator *comm;

public:
	ReductionManager(ICommunicator *cm) : comm(cm) {}
	~ReductionManager() {}

	//void registerReductionCF(unsigned int red_id, ReductionCompFragment *cf);
	void registerReductionCFs(const unsigned int& red_id, const ReductionCompFragmentPtrArray& cfs);
	double waitForReductionResult(const unsigned int& red_id);

	//void onCFDone(CompFragment *cf);
	void onCFsDone(const CompFragmentPtrArray& cfs);
};
