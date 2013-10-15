#include "cfcoef.h"
#include "cnst.h"
#include <boost/foreach.hpp>

void CFCoef::exec(MeshFragment& mesh, DataCoef& data_coef) {	
	if(data_coef.empty())
		data_coef.resize(mesh.nodes.size());

	for(unsigned int i = 0;i < data_coef.size();i++) {	// for each data elem
		NodeDataCoef& dt = data_coef[i];
		const MeshNode& n = mesh.nodes[i];
		const double sin_phi = sin(n.phi);	
		const double r_h_sin = sin_phi*cnst::RADIUS*n.depth;

		dt.b1 = -r_h_sin*cnst::OMEGA2*cos(n.phi);
		dt.c1 = n.depth*cnst::G;
		dt.c2 = dt.c1*sin_phi;
		dt.e0 = r_h_sin*cnst::TAU1;
		dt.gamma2 = sqrt(dt.c1)*cnst::G;
		dt.gamma1 = dt.gamma2*cnst::BETA;
	}
}
