#include "auxilary.h"

namespace aux {

void sliceMesh(const unsigned int& mesh_nodes_num, const unsigned int &fragments_num, std::vector<unsigned int>& start, std::vector<unsigned int>& length) {
	const unsigned int size = mesh_nodes_num + fragments_num - 1;	// size of mesh, including doubled vertices 
	const unsigned int d = size % fragments_num;
	start.resize(fragments_num);
	length.resize(fragments_num);
	unsigned int prev = 0;	
	for(unsigned int i = 0;i < fragments_num;i++) {	// for each fragment
		start[i] = prev;	// index of a first node in a fragment
		length[i] = size/fragments_num + ((i < d) ? 1 : 0);	// distribute nodes among fragments
		prev += length[i] - 1;
	}	
}

void distributeFragments(const unsigned int& fragments_num, const unsigned int& node_rank, const unsigned int& node_size, unsigned int& start, unsigned int& end) {
	const unsigned int size = fragments_num / node_size;
	const unsigned int d = fragments_num % node_size;
	start = node_rank*size + (node_rank < d ? node_rank : d);
	end = start + size + (node_rank < d ? 1 : 0);
}

}
