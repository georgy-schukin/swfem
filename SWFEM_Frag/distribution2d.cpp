#include "distribution2d.h"
#include <vector>

void Distribution2D::distribute(const size_t& size_x, const size_t& size_y, const size_t& num_of_nodes_by_x, const size_t& num_of_nodes_by_y) {
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