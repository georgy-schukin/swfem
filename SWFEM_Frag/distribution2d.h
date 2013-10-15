#pragma once

#include "distribution.h"
#include "distributionblock2d.h"
#include <vector>

/**
* Block 2D distribution for 2d arrays
*/
class Distribition2D : public Distribution<DistributionBlock2D> {
private:
	size_t num_of_nodes_by_x;
	size_t num_of_nodes_by_y;

private:
	void distribute(const size_t& size_x, const size_t& size_y, const size_t& num_of_nodes_by_x, const size_t& num_of_nodes_by_y) {
		const size_t sx = size_x / num_of_nodes_by_x;
		const size_t sy = size_y / num_of_nodes_by_y;
		const size_t dx = size_x % num_of_nodes_by_x;
		const size_t dy = size_y % num_of_nodes_by_y;

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
	Distribition2D(const size_t& size_x, const size_t& size_y, const size_t& num_of_nodes_by_x, const size_t& num_of_nodes_by_y) {
		this->num_of_nodes_by_x = num_of_nodes_by_x;
		this->num_of_nodes_by_y = num_of_nodes_by_y;
		this->distribute(size_x, size_y, num_of_nodes_by_x, num_of_nodes_by_y);				
	}
	~Distribition2D() {}

	size_t getNumOfNodesByX() const {
		return num_of_nodes_by_x;
	}

	size_t getNumOfNodesByY() const {
		return num_of_nodes_by_y;
	}

	const DistributionBlock2D& getBlock(const size_t& node_x, const size_t& node_y) const {
		return this->get(node_y*num_of_nodes_by_x + node_x);
	}
};
