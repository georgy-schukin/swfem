#pragma once

#include <vector>

namespace aux {

/**
* Slice mesh (in one dimension, with mesh_nodes_num nodes) on fragments_num fragments
* start - index of start point in fragments, length - num of points in fragments
* Slicing takes in accoint that border nodes are doubled in border fragments ([n1,n2,n3], [n3,n4,n5], [n5,n6], etc.)
*/
void sliceMesh(const size_t& mesh_nodes_num, const size_t &fragments_num, std::vector<size_t>& start, std::vector<size_t>& length);

/**
* Distribute fragments_num fragments among node_size nodes (in one dimension)
* For node_rank node get indices of start and end fragments [start, end)
*/
void distributeFragments(const size_t& fragments_num, const size_t& node_rank, const size_t& node_size, size_t& start, size_t& end);

}