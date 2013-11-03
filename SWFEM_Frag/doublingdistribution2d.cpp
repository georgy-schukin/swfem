#include "doublingdistribution2d.h"

void DoublingDistribution2D::computeRegions(const size_t& size, const size_t& num, std::vector<Region>& result) {
	const size_t size_with_doubles = size + num - 1;
	const size_t region_size = size_with_doubles/num;
	const size_t rest = size_with_doubles % num;
		
	size_t prev = 0;
	for (size_t i = 0; i < num; i++) {			
		const size_t start = prev; // start
		const size_t end = start + region_size + (i < rest ? 1 : 0); // end
		prev = end - 1;
		result.push_back(Region(start, end));
	}
}