#include "cfdiag.h"
#include "cnst.h"

void CFDiag::exec(MeshFragment& mesh, DataCoef& data_coef, DataInteraction& data_interaction) {	
	if(data_coef.empty()) 
		data_coef.resize(mesh.nodes.size());

	for(unsigned int i = 0;i < data_coef.size();i++) {
		NodeDataCoef& dt = data_coef[i];
		NodeDataInteraction& dti = data_interaction[i];
		const MeshNode& n = mesh.nodes[i];		
		const double r_sin = sin(n.phi)*cnst::RADIUS;		
		const double r_h_sin = r_sin*n.depth;

		dt.a1 = r_sin*n.depth*(cnst::TAU1 + dt.rr);
		dt.a3 = r_sin*cnst::G*cnst::TAU1;		

		dt.e1 = r_h_sin*dti.w1;
		dt.e2 = r_h_sin*dti.w2;
		dt.e3 = r_sin*cnst::G*dti.w3;		
	}
}
