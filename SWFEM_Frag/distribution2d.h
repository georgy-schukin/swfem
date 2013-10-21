#pragma once

#include "distribution.h"
#include "distributionblock2d.h"
#include <vector>

/**
* Block 2D distribution for 2d arrays
*/
class Distribution2D : private Distribution<DistributionBlock2D> {
private:
	size_t size_x;
	size_t size_y;
	size_t num_of_nodes_by_x;
	size_t num_of_nodes_by_y;

private:
	void distribute(const size_t& size_x, const size_t& size_y, const size_t& num_of_nodes_by_x, const size_t& num_of_nodes_by_y) {
		const size_t sx = size_x / num_of_nodes_by_x;
		const size_t sy = size_y / num_of_nodes_by_y;
		const size_t dx = size_x % num_of_nodes_by_x;
		const size_t dy = size_y % num_of_nodes_by_y;

		this->clear();
		for ( size_t node_y = 0; node_y < num_of_nodes_by_y; node_y++) {
			for ( size_t node_x = 0; node_x < num_of_nodes_by_x; node_x++) {		
				const size_t start_x = node_x*sx + (node_x < dx ? node_x : dx); // distr by X
				const size_t start_y = node_y*sy + (node_y < dy ? node_y : dy); // distr by Y
				const size_t end_x = start_x + sx + (node_x < dx ? 1 : 0);
				const size_t end_y = start_y + sy + (node_y < dy ? 1 : 0);
				this->set(node_y*num_of_nodes_by_x + node_x, DistributionBlock2D(start_x, start_y, end_x, end_y));
			}
		}
	}

public:
	Distribution2D(const size_t& sx, const size_t& sy, const size_t& nx, const size_t& ny) :
		size_x(sx), size_y(sy), num_of_nodes_by_x(nx), num_of_nodes_by_y(ny) {		
		distribute(sx, sy, nx, ny);				
	}
	Distribution2D(const Distribution2D& distr) : Distribution(distr), 
		size_x(distr.size_x), size_y(distr.size_y), num_of_nodes_by_x(distr.num_of_nodes_by_x), num_of_nodes_by_y(distr.num_of_nodes_by_y) {}
	~Distribution2D() {}

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

	void init(const size_t& sx, const size_t& sy, const size_t& nx, const size_t& ny) {
		size_x = sx;
		size_y = sy;
		num_of_nodes_by_x = nx;
		num_of_nodes_by_y = ny;
		distribute(sx, sy, nx, ny);
	}

	const DistributionBlock2D& getBlock(const size_t& node_x, const size_t& node_y) const {
		return this->get(node_y*num_of_nodes_by_x + node_x);
	}

	const DistributionBlock2D& getBlock(const size_t& node) const {
		return this->get(node);
	}
};
