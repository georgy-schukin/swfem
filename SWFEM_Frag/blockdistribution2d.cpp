#include "blockdistribution2d.h"

void BlockDistribution2D::computeRegions(const size_t& size, const size_t& num, std::vector<Region>& result) {
	const size_t region_size = size/num;
	const size_t rest = size % num;
		
	for (size_t i = 0; i < num; i++) {			
		const size_t start = i*region_size + (i < rest ? i : rest); // start
		const size_t end = start + region_size + (i < rest ? 1 : 0); // end
		result.push_back(Region(start, end));
	}
}