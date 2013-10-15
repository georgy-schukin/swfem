#pragma once

#include "compfragment.h"
#include "mesh.h"
#include <string>

/*
* Load mesh points from file
*	mesh: mesh data to fill
*	filename - name of a file with a mesh points data
*	step - num of points to skip in the file
*	size - num of points to load from a file
*/
class CFLoadPoints: public CompFragment {
protected:
	string filename; 
public:
	CFLoadPoints(MeshFragment *mesh, const std::string& file) : filename(file) {
		addArg(mesh);
	}
	~CFLoadPoints() {}

	void execute() {
		exec(getArg<MeshFragment>(0), filename, 0, 0);
	}

	void exec(MeshFragment& mesh, const std::string& filename, unsigned int step, unsigned int size);	
};
