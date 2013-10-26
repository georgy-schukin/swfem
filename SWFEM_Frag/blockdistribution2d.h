#pragma once

#include "distribution2d.h"
#include "region.h"
#include <vector>

/**
* Block distribution - distribute by regular blocks
*/
class BlockDistribution2D : public Distribution2D {
protected:
	virtual void computeRegions(const size_t& size, const size_t& num, std::vector<Region>& result) {
		const size_t region_size = size/num;
		const size_t rest = size % num;
		
		for (size_t i = 0; i < num; i++) {			
			const size_t start = i*region_size + (i < rest ? i : rest); // start
			const size_t end = start + region_size + (i < rest ? 1 : 0); // end
			result.push_back(Region(start, end));
		}
	}

public:
	BlockDistribution2D() {}
	BlockDistribution2D(const size_t& sx, const size_t& sy, const size_t& nx, const size_t& ny) : Distribution2D(sx, sy, nx, ny) {
		distribute(sx, sy, nx, ny);
	}	
	//BlockDistribution2D(const BlockDistribution2D& d) : Distribution2D(d) {}
	~BlockDistribution2D() {}
};