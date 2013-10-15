#include "cfjacobydiag.h"
#include "cnst.h"
#include <boost/foreach.hpp>

/*
* Count diag elems for Jacoby method
*/
void CFJacobyDiag::exec(MeshFragment& mesh, Data& data_diag, DataCoef& data_coef) {	
	if(data_diag.empty()) 
		data_diag.resize(mesh.nodes.size());

	BOOST_FOREACH(NodeData& diag, data_diag) {
		diag.u = 0.0;
		diag.v = 0.0;
		diag.xi = 0.0;
	}

	BOOST_FOREACH(const MeshTriangle &tr, mesh.triangles) {	// for each triangle	
		const unsigned int ind[3] = {tr.n[0], tr.n[1], tr.n[2]};
			/*mesh.global_to_local[tr.n[0]],	// local indices for nodes
			mesh.global_to_local[tr.n[1]],
			mesh.global_to_local[tr.n[2]]};				*/

		for(unsigned int j = 0; j < 3; j++){	// for each point in triangle						
			NodeData& diagj = data_diag[ind[j]];	// get diag data, corresponding to the node
			const NodeDataCoef& coefj = data_coef[ind[j]];		// get coef data, corresponding to the node 			

			diagj.u = diagj.u + coefj.a1*tr.square;		// the first equation
			diagj.v = diagj.v + coefj.a1*tr.square;		// the second equation
			diagj.xi = diagj.xi + coefj.a3*tr.square;	// the third equation		
			
			/*if ((tr.edge[j] == -1) || (tr.edge[j] == -7)) {
				const unsigned int k = (j + 1)%3;
				//const NodeDataDiag& diagk = data_diag.data[ind[k]];	
				const MeshNode& nj = mesh.nodes[ind[j]];
				const MeshNode& nk = mesh.nodes[ind[k]];
				const double hlp1 = nk.phi - nj.phi;
				const double hlp2 = (nk.lambda - nj.lambda)*sin(nj.phi);
				const double hlp3 = fabs(sqrt(hlp1*hlp1 + hlp2*hlp2))/2.0;		
				diagj.xi = diagj.xi + hlp3*coefj.gamma1;				
			}*/
		}
	}
}
