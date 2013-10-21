#include "cfloadtriangles.h"
#include <iostream>
#include <fstream>

using namespace std;

void CFLoadTriangles::exec(MeshFragment& mesh, const std::string& filename, size_t step, size_t size) {
	std::ifstream f_in(filename.c_str(), ios::in);
	if(!f_in.is_open()) {
		cerr << "Error: can't open " << filename << endl;
		return;
	}
	size_t num;
		f_in >> num;
	mesh.triangles.resize(num);
	for(size_t i = 0; i < num;i++) {
		MeshTriangle& tr = mesh.triangles[i];
		f_in >> tr.id >> tr.n[0] >> tr.n[1] >> tr.n[2] >>
			tr.edge[0] >> tr.edge[1] >> tr.edge[2];
	}
	f_in.close();
}
