#pragma once

#include "distribution.h"
#include "region.h"
#include "region2d.h"
#include <vector>

/**
* 2D distribution
*/
class Distribution2D : protected Distribution<Region2D> {
protected:
	size_t size_x;
	size_t size_y;
	size_t num_of_nodes_by_x;
	size_t num_of_nodes_by_y;

protected:
	virtual void computeRegions(const size_t& size, const size_t& num, std::vector<Region>& result) = 0;

	void distribute(const size_t& size_x, const size_t& size_y, const size_t& num_of_nodes_by_x, const size_t& num_of_nodes_by_y) {
		std::vector<Region> regions_by_x, regions_by_y;

		computeRegions(size_x, num_of_nodes_by_x, regions_by_x);
		computeRegions(size_y, num_of_nodes_by_y, regions_by_y);		
		
		for ( size_t node_y = 0; node_y < num_of_nodes_by_y; node_y++) {
			for ( size_t node_x = 0; node_x < num_of_nodes_by_x; node_x++) {						
				const Region& rx = regions_by_x[node_x];
				const Region& ry = regions_by_y[node_y];
				this->set(node_y*num_of_nodes_by_x + node_x, 
					Region2D(rx.getStart(), ry.getStart(), rx.getEnd(), ry.getEnd()));
			}
		}
	}

protected:
	Distribution2D() : size_x(0), size_y(0), num_of_nodes_by_x(0), num_of_nodes_by_y(0) {}	 
	Distribution2D(const size_t& sx, const size_t& sy, const size_t& nx, const size_t& ny) :
		size_x(sx), size_y(sy), num_of_nodes_by_x(nx), num_of_nodes_by_y(ny) {}	
	//Distribution2D(const Distribution2D& d) : Distribution(d),
	//	size_x(d.size_x), size_y(d.size_y), num_of_nodes_by_x(d.num_of_nodes_by_x), num_of_nodes_by_y(d.num_of_nodes_by_y) {}
	~Distribution2D() {}

public:
	size_t getSizeByX() const {
		return size_x;
	}

	size_t getSizeByY() const {
		return size_y;
	}

	size_t getNumOfNodesByX() const {
		return num_of_nodes_by_x;
	}

	size_t getNumOfNodesByY() const {
		return num_of_nodes_by_y;
	}

	const Region2D& getBlock(const size_t& node_x, const size_t& node_y) const {
		return this->get(node_y*num_of_nodes_by_x + node_x);
	}

	const Region2D& getBlock(const size_t& node) const {
		return this->get(node);
	}
};
