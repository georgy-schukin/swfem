#pragma once

#include "distribution2d.h"
#include <vector>

/**
* Doubling distribution - doubles border elements (for mesh, for example)
*/
class DoublingDistribution2D : public Distribution2D {
protected:
	virtual void computeRegions(const size_t& size, const size_t& num, std::vector<Region>& result);

public:
	DoublingDistribution2D() {}
	DoublingDistribution2D(const size_t& sx, const size_t& sy, const size_t& nx, const size_t& ny) : Distribution2D(sx, sy, nx, ny) {
		distribute(sx, sy, nx, ny);
	}	
	//DoublingDistribution2D(const DoublingDistribution2D& d) : Distribution2D(d) {}
	~DoublingDistribution2D() {}
};
