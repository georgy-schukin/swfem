#include "auxilary.h"

namespace aux {

void sliceMesh(const size_t& mesh_nodes_num, const size_t &fragments_num, std::vector<size_t>& start, std::vector<size_t>& length) {
	const size_t size = mesh_nodes_num + fragments_num - 1;	// size of mesh, including doubled vertices 
	const size_t d = size % fragments_num;
	start.resize(fragments_num);
	length.resize(fragments_num);
	size_t prev = 0;	
	for(size_t i = 0;i < fragments_num;i++) {	// for each fragment
		start[i] = prev;	// index of a first node in a fragment
		length[i] = size/fragments_num + ((i < d) ? 1 : 0);	// distribute nodes among fragments
		prev += length[i] - 1;
	}	
}

void distributeFragments(const size_t& fragments_num, const size_t& node_rank, const size_t& node_size, size_t& start, size_t& end) {
	const size_t size = fragments_num / node_size;
	const size_t d = fragments_num % node_size;
	start = node_rank*size + (node_rank < d ? node_rank : d);
	end = start + size + (node_rank < d ? 1 : 0);
}

}
