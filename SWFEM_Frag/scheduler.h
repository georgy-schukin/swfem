#include "ischeduler.h"
#include <vector>
#include <set>
#include <map>

class Scheduler : public IScheduler {
protected:
	unsigned int num_of_threads;
	//map<unsigned int, unsigned int> dfs_placement;	// affinity of data to threads
	//vector<unsigned int> thread_weight;		// accum weight of data on threads
	int step;

protected:
	unsigned int getIndexWithMinValue(const std::vector<unsigned int>& v);
	unsigned int getIndexWithMaxValue(const std::vector<unsigned int>& v);

public:
	Scheduler(const unsigned int& num_of_threads);
	~Scheduler() {}

	//unsigned int scheduleCF(CompFragment *cf);
	void scheduleCFs(const CompFragmentPtrArray& cfs, std::vector<unsigned int>& thread_ids);
};
