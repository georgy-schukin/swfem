#pragma once

#include "compfragment.h"
#include "mesh.h"
#include <string>

/*
* Load mesh triangles from file
*	mesh: mesh data to fill
*	filename - name of a file with a mesh points data
*	step - num of points to skip in the file
*	size - num of points to load from a file
*/
class CFLoadTriangles: public CompFragment {
public:
	void exec(MeshFragment& mesh, const std::string& filename, size_t step, size_t size);
};
