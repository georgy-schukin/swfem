#include "icfscheduler.h"
#include <vector>
#include <set>
#include <map>

class CFScheduler : public ICFScheduler {
protected:
	size_t num_of_threads;
	ICFExecutor *executor;
	//map<size_t, size_t> dfs_placement;	// affinity of data to threads
	//vector<size_t> thread_weight;		// accum weight of data on threads
	//int step;

protected:
	size_t getIndexWithMinValue(const std::vector<size_t>& v);
	size_t getIndexWithMaxValue(const std::vector<size_t>& v);

public:
	CFScheduler(const size_t& n) : num_of_threads(n) {}
	~CFScheduler() {}

	virtual void scheduleCF(CompFragment *cf);
	virtual void scheduleCFs(CompFragmentPtrArray& cfs);	
};
