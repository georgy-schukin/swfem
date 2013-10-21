#include "cfexact.h"
#include "cnst.h"

/*
* Count exact solution by formulae
*/
void CFExact::exec(MeshFragment& mesh, Data& data) {
	if(data.empty()) 
		data.resize(mesh.nodes.size());

	const double lmbd0 = 0.0;
	const double lmbd1 = cnst::PI/18.0; 
	const double phi0 = cnst::PI_DIV_2;
	const double phi1 = cnst::PI_DIV_2 + cnst::PI/18.0;	

	const double t1 = 1000.0 + tt;
	const double t2 = pow(t1, 0.3333333333333333);
	const double t3 = 72.0;
	const double t4 = 72.0*72.0;	

	for(size_t i = 0;i < data.size();i++) {
		const MeshNode& n = mesh.nodes[i];
		NodeData& dt = data[i];

		const double t5 = sin((n.lambda - lmbd0)*t3);
		const double t6 = cos((n.phi - phi0)*t3);		
		const double t7 = cos((n.lambda - lmbd0)*t3);
		const double t8 = sin((n.phi - phi0)*t3);
		const double t9 = sin(n.phi);

		dt.u = 100000.0*t3*t5*t6/(3.0*t1*t2*n.depth);
		dt.v = 100000.0*t3*t7*t8/(3.0*t1*t2*t9*n.depth);		
		dt.xi = -200000.0*t4*t6*t7/(t2*t9*cnst::RADIUS);
	}
}
