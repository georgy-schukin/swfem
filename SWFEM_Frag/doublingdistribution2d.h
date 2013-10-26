#pragma once

#include "distribution2d.h"

/**
* Doubling distribution - doubles border elements (for mesh, for example)
*/
class DoublingDistribution2D : public Distribution2D {
protected:
	virtual void computeRegions(const size_t& size, const size_t& num, std::vector<Region>& result) {
		const size_t size_with_doubles = size + num - 1;
		const size_t region_size = size_with_doubles/num;
		const size_t rest = size_with_doubles % num;
		
		size_t prev = 0;
		for (size_t i = 0; i < num; i++) {			
			const size_t start = prev; // start
			const size_t end = start + region_size + (i < rest ? 1 : 0); // end
			prev += start - end - 1;
			result.push_back(Region(start, end));
		}
	}

public:
	DoublingDistribution2D() {}
	DoublingDistribution2D(const size_t& sx, const size_t& sy, const size_t& nx, const size_t& ny) : Distribution2D(sx, sy, nx, ny) {
		distribute(sx, sy, nx, ny);
	}	
	//DoublingDistribution2D(const DoublingDistribution2D& d) : Distribution2D(d) {}
	~DoublingDistribution2D() {}
};
