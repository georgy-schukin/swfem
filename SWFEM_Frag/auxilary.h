#pragma once

#include <vector>

namespace aux {

/**
* Slice mesh (in one dimension, with mesh_nodes_num nodes) on fragments_num fragments
* start - index of start point in fragments, length - num of points in fragments
* Slicing takes in accoint that border nodes are doubled in border fragments ([n1,n2,n3], [n3,n4,n5], [n5,n6], etc.)
*/
void sliceMesh(const unsigned int& mesh_nodes_num, const unsigned int &fragments_num, std::vector<unsigned int>& start, std::vector<unsigned int>& length);

/**
* Distribute fragments_num fragments among node_size nodes (in one dimension)
* For node_rank node get indices of start and end fragments [start, end)
*/
void distributeFragments(const unsigned int& fragments_num, const unsigned int& node_rank, const unsigned int& node_size, unsigned int& start, unsigned int& end);

}