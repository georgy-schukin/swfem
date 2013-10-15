#include "cfjacobymultdirect.h"
#include <boost/foreach.hpp>

/*
* Do iteration of Jacoby method for mesh fragment
*/ 
void CFJacobyMultDirect::exec(MeshFragment& mesh, Data& data_new, Data& data, Data& data_prev, DataCoef& data_coef) {
	if(data_new.empty()) 
		data_new.resize(mesh.nodes.size());

	BOOST_FOREACH(NodeData& dnew, data_new) {
		dnew.u = 0.0;
		dnew.v = 0.0;
		dnew.xi = 0.0;
	}

	BOOST_FOREACH(const MeshTriangle& tr, mesh.triangles) {	// for each triangle in mesh
		/*const unsigned int i1 = mesh.global_to_local[tr.n[0]];
		const unsigned int i2 = mesh.global_to_local[tr.n[1]];
		const unsigned int i3 = mesh.global_to_local[tr.n[2]];*/
		const unsigned int i1 = tr.n[0];
		const unsigned int i2 = tr.n[1];
		const unsigned int i3 = tr.n[2];
		const unsigned int ind[3] = {i1, i2, i3};			

		const MeshNode& n1 = mesh.nodes[i1];	// get points of triangle
		const MeshNode& n2 = mesh.nodes[i2];
		const MeshNode& n3 = mesh.nodes[i3];

		const NodeData& dt1 = data[i1];	// data, corresponding to the node 
		const NodeData& dt2 = data[i2];	
		const NodeData& dt3 = data[i3];	
		
		for (unsigned int j = 0; j < 3; j++) {			// for each node in triangle
			NodeData& dnew = data_new[ind[j]];			// get data, corresponding to the node 
			NodeData& dt = data[ind[j]];				// get data, corresponding to the node 
			NodeData& dprev = data_prev[ind[j]];		// get data, corresponding to the node 
			NodeDataCoef& coef = data_coef[ind[j]];		// get data, corresponding to the node 			

			// the first equation
			dnew.u = dnew.u
				+ dt.u*coef.a1*tr.square
				- dt.v*coef.b1*tr.square
				- ((n2.phi - n3.phi)*dt1.xi
				+ (n3.phi - n1.phi)*dt2.xi
				+ (n1.phi - n2.phi)*dt3.xi)*coef.c1/6.0
				- tr.square*(coef.e1 + dprev.u*coef.e0);					

			// the second equation
			const double sum1 = (n3.lambda - n2.lambda)*dt1.xi
				+ (n1.lambda - n3.lambda)*dt2.xi 
				+ (n2.lambda - n1.lambda)*dt3.xi;				

			dnew.v = dnew.v
				+ dt.v*coef.a1*tr.square
				+ dt.u*coef.b1*tr.square
				- sum1*coef.c2/6.0
				- tr.square*(coef.e2 + dprev.v*coef.e0);				
		}

		// the third equation		
		const NodeDataCoef& coef1 = data_coef[i1];	// coef, corresponding to the node 
		const NodeDataCoef& coef2 = data_coef[i2];	
		const NodeDataCoef& coef3 = data_coef[i3];	

		double sum2 = (coef1.c1*dt1.u + coef2.c1*dt2.u + coef3.c1*dt3.u)/6.0;
		double sum3 = (coef1.c2*dt1.v + coef2.c2*dt2.v + coef3.c2*dt3.v)/6.0;						

		data_new[i1].xi = data_new[i1].xi
			+ dt1.xi*coef1.a3*tr.square
			+ sum2*(n2.phi - n3.phi)
			+ sum3*(n3.lambda - n2.lambda)
			- tr.square*(coef1.e3 + data_prev[i1].xi*coef1.a3);			

		data_new[i2].xi = data_new[i2].xi
			+ dt2.xi*coef2.a3*tr.square
			+ sum2*(n3.phi - n1.phi)
			+ sum3*(n1.lambda - n3.lambda)
			- tr.square*(coef2.e3 + data_prev[i2].xi*coef2.a3);			

		data_new[i3].xi = data_new[i3].xi
			+ dt3.xi*coef3.a3*tr.square
			+ sum2*(n1.phi - n2.phi)
			+ sum3*(n2.lambda - n1.lambda)
			- tr.square*(coef3.e3 + data_prev[i3].xi*coef3.a3);									

		/*for(unsigned int j = 0; j < 3; j++) { // the side of triangle cycle
			const unsigned int k = (j + 1)%3;
			if ((tr.edge[j] == -1) || (tr.edge[j] == -7)) {
				const MeshNode& nj = mesh.nodes[ind[j]];
				const MeshNode& nk = mesh.nodes[ind[k]];				
				const NodeDataCoef& coefj = data_coef[ind[j]];
				const NodeDataCoef& coefk = data_coef[ind[k]];
				
				const double hlp1 = nk.phi - nj.phi;
				const double hlp2 = (nk.lambda - nj.lambda)*sin(nj.phi);
				const double hlp3 = fabsl(sqrtl(hlp1*hlp1 + hlp2*hlp2))/2.0;
				const double hlp4 = (nk.lambda - nj.lambda)*sin(nk.phi);
				const double hlp5 = fabsl(sqrtl(hlp1*hlp1 + hlp4*hlp4))/2.0;

				data_new[ind[j]].xi = data_new[ind[j]].xi
					+ data[ind[j]].xi*hlp3*coefj.gamma1
					- hlp3*coefj.d_bc*coefj.gamma2;

				data_new[ind[k]].xi = data_new[ind[k]].xi
					+ data[ind[k]].xi*hlp5*coefk.gamma1
					- hlp5*coefk.d_bc*coefk.gamma2;					
			}
		}*/
	}
}
