#include "cfinit.h"
#include <boost/foreach.hpp>

/*
* Init data
*/
void CFInit::exec(MeshFragment& mesh, Data& data, DataCoef& data_coef) {
	if(data.empty())
		data.resize(mesh.nodes.size());	// create data elems
	if(data_coef.empty())
		data_coef.resize(mesh.nodes.size());	// create data elems

	BOOST_FOREACH(MeshTriangle& tr, mesh.triangles) {	// update mesh - count square of triangles
		/*const unsigned int ind[3] = {
			mesh.global_to_local[tr.n[0]],	// local indices for nodes
			mesh.global_to_local[tr.n[1]],
			mesh.global_to_local[tr.n[2]]};*/

		const MeshNode& n1 = mesh.nodes[tr.n[0]];	// get points of triangle
		const MeshNode& n2 = mesh.nodes[tr.n[1]];
		const MeshNode& n3 = mesh.nodes[tr.n[2]];

		tr.square = (n1.lambda*(n2.phi - n3.phi)	// count square
			  + n2.lambda*(n3.phi - n1.phi)
			  + n3.lambda*(n1.phi - n2.phi))/6.0;
	}

	BOOST_FOREACH(NodeDataCoef& dtc, data_coef) {
		dtc.rr = 1.0e-5;
	}
}
