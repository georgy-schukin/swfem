#pragma once

#include "datafragment.h"
#include "meshnode.h"
#include "meshtriangle.h"
#include <vector>

/*
* MeshFragment fragment - array of nodes and triangles
*/
class MeshFragment: public DataFragment {
public:
	std::vector<MeshNode> nodes;
	std::vector<MeshTriangle> triangles;
	//std::vector<size_t> border;
	//map<size_t, size_t> local_to_global; // node local index -> node global id
	//map<size_t, size_t> global_to_local; // node global id -> node local index	

public:
	MeshFragment() {}
	~MeshFragment() {}

	size_t getWeight() {
		return sizeof(MeshNode)*nodes.size() + sizeof(MeshTriangle)*triangles.size() + 1;
	}
};
