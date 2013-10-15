#pragma once

#include "compfragment.h"
#include "mesh.h"

/**
* Generate mesh fragment
*/
class CFGen: public CompFragment {
protected: 
	double beg_x;				// start coordinate by labmda
	double beg_y;				// start coordinate by phi
	double step_x;				// step (between points) by lambda
	double step_y;				// step by phi
	unsigned int global_num_x;	// num of points by lambda in the whole mesh
	unsigned int global_num_y;	// num of points by phi
	unsigned int start_x;		// start index of points by lambda for the mesh fragment
	unsigned int start_y;		// start index by phi
	unsigned int num_x;			// num of points in the mesh fragment by lambda
	unsigned int num_y;			// num of points by phi

public:
	CFGen(double bx, double by, double sx, double sy, unsigned int gnx, unsigned int gny,
		unsigned int stx, unsigned int sty, unsigned int nx, unsigned int ny) : 
		beg_x(bx), beg_y(by), step_x(sx), step_y(sy), global_num_x(gnx), global_num_y(gny),
			start_x(stx), start_y(sty), num_x(nx), num_y(ny) {}
	CFGen(MeshFragment *mesh, double bx, double by, double sx, double sy, unsigned int gnx, unsigned int gny,
		unsigned int stx, unsigned int sty, unsigned int nx, unsigned int ny) : 
		beg_x(bx), beg_y(by), step_x(sx), step_y(sy), global_num_x(gnx), global_num_y(gny),
		start_x(stx), start_y(sty), num_x(nx), num_y(ny) {
		addArg(mesh);
	}
	~CFGen() {}

	void execute() {
		exec(getArg<MeshFragment>(0));
	}

	void exec(MeshFragment& mesh);	

	std::string toString() const {
		return "Gen " + CompFragment::toString();
	}
};
