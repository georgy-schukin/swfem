#include "cfloadpoints.h"
#include <iostream>
#include <fstream>

using namespace std;

void CFLoadPoints::exec(MeshFragment& mesh, const std::string& filename, size_t step, size_t size) {
	std::ifstream f_in(filename.c_str(), ios::in);
	if(!f_in.is_open()) {
		cerr << "Error: can't open " << filename << endl;
		return;
	}
	size_t num;
		f_in >> num;
	mesh.nodes.resize(num);
	for(size_t i = 0; i < num;i++) {
		MeshNode& node = mesh.nodes[i];
		f_in >> node.id >> node.lambda >> node.phi >> node.depth;
	}
	f_in.close();
}
