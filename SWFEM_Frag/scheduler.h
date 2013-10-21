#include "ischeduler.h"
#include <vector>
#include <set>
#include <map>

class Scheduler : public IScheduler {
protected:
	size_t num_of_threads;
	//map<size_t, size_t> dfs_placement;	// affinity of data to threads
	//vector<size_t> thread_weight;		// accum weight of data on threads
	int step;

protected:
	size_t getIndexWithMinValue(const std::vector<size_t>& v);
	size_t getIndexWithMaxValue(const std::vector<size_t>& v);

public:
	Scheduler(const size_t& num_of_threads);
	~Scheduler() {}

	//size_t scheduleCF(CompFragment *cf);
	void scheduleCFs(const CompFragmentPtrArray& cfs, std::vector<size_t>& thread_ids);
};
