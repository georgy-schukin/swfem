#include "cfgen.h"
#include "cnst.h"
#include <iostream>

/*
* Generate mesh fragment (points and triangles)
*/
void CFGen::exec(MeshBlockFragment& mesh) {	
	try {
	//mesh.nodes.reserve(num_x*num_y);
		mesh.setSizeByX(num_x);
		mesh.setSizeByY(num_y);
	mesh.nodes.resize(num_x*num_y);
	for(size_t i = 0;i < num_y;i++)		// generate points
	for(size_t j = 0;j < num_x;j++) {
		MeshNode& n = mesh.nodes[i*num_x + j];
		n.lambda = (beg_x + (j + start_x)*step_x)*cnst::PI_DIV_180;		// lambda coord (by x) in radians
		n.phi = (beg_y + (i + start_y)*step_y)*cnst::PI_DIV_180;		// phi coord (by y) in radians
		n.depth = 1000.0;
		//mesh.global_to_local[(start_y + i)*global_num_x + start_x + j] = i*num_x + j;
	}

	//mesh.triangles.reserve((num_x - 1)*(num_y - 1)*2);
	mesh.triangles.resize((num_x - 1)*(num_y - 1)*2);
	for(size_t i = 0;i < num_y - 1;i++)	// generate triangles
	for(size_t j = 0;j < num_x - 1;j++) {
		const size_t lb = i*num_x + j;
		const size_t rb = i*num_x + j + 1;
		const size_t lt = (i + 1)*num_x + j; 
		const size_t rt = (i + 1)*num_x + j + 1;
		MeshTriangle& t1 = mesh.triangles[2*(i*(num_x - 1) + j)];
		MeshTriangle& t2 = mesh.triangles[2*(i*(num_x - 1) + j) + 1];
		t1.n[0] = lb;	// top triangle
		t1.n[1] = rt;
		t1.n[2] = lt;
		t2.n[0] = lb;	// bottom triangle
		t2.n[1] = rb;
		t2.n[2] = rt;
		/*t1.edge[0] = 0;	// edge types for top triangle
		t1.edge[1] = 1;//(i + start_y + 1 == global_num_y - 1) ? -1 : 0;
		t1.edge[2] = (j + start_x == 0) ? 1 : 0;
		t2.edge[0] = (i + start_y == 0) ? 1 : 0;	// edge types for bottom triangle
		t2.edge[1] = 1;//(j + start_x + 1 == global_num_x - 1) ? -1 : 0;
		t2.edge[2] = 0;*/
	}	
	} 
	catch (...) {
		std::cerr << "Error!" << std::endl;
	}
}
