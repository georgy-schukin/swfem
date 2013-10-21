#pragma once

#include "compfragment.h"
#include "meshblockfragment.h"

/**
* Generate mesh fragment
*/
class CFGen: public CompFragment {
protected: 
	double beg_x;				// start coordinate by labmda
	double beg_y;				// start coordinate by phi
	double step_x;				// step (between points) by lambda
	double step_y;				// step by phi
	size_t global_num_x;	// num of points by lambda in the whole mesh
	size_t global_num_y;	// num of points by phi
	size_t start_x;		// start index of points by lambda for the mesh fragment
	size_t start_y;		// start index by phi
	size_t num_x;			// num of points in the mesh fragment by lambda
	size_t num_y;			// num of points by phi

public:
	CFGen(double bx, double by, double sx, double sy, size_t gnx, size_t gny,
		size_t stx, size_t sty, size_t nx, size_t ny) : 
		beg_x(bx), beg_y(by), step_x(sx), step_y(sy), global_num_x(gnx), global_num_y(gny),
			start_x(stx), start_y(sty), num_x(nx), num_y(ny) {}
	CFGen(MeshBlockFragment *mesh, double bx, double by, double sx, double sy, size_t gnx, size_t gny,
		size_t stx, size_t sty, size_t nx, size_t ny) : 
		beg_x(bx), beg_y(by), step_x(sx), step_y(sy), global_num_x(gnx), global_num_y(gny),
		start_x(stx), start_y(sty), num_x(nx), num_y(ny) {
		addArg(mesh);
	}
	~CFGen() {}

	void execute() {
		exec(getArg<MeshBlockFragment>(0));
	}

	void exec(MeshBlockFragment& mesh);	

	std::string toString() const {
		return "Gen " + CompFragment::toString();
	}
};
