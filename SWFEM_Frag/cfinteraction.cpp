#include "cfinteraction.h"
#include "cnst.h"

void CFInteraction::exec(MeshFragment& mesh, DataInteraction& data_interaction) {
	if(data_interaction.empty()) 
		data_interaction.resize(mesh.nodes.size());

	const double lmbd0 = 0.0;
	const double lmbd1 = cnst::PI/18.0;
	const double phi0 = cnst::PI_DIV_2;
	const double phi1 = cnst::PI_DIV_2 + cnst::PI/18.0;
	
	const double t_x = 1.0/72.0;
	const double t_y = 1.0/72.0;

	const double t1 = 1000.0 + tt;
	const double t2 = t1*t1;
	const double t3 = pow(t1, 0.3333333333333333);
	const double t4 = 1.0/t_x;
	const double t5 = 1.0/t_y;	
	const double t12 = t_x*t_x;
	const double t13 = t_y*t_y;				

	const double t14 = 1.0/(t1*t3);
	const double t17 = cnst::RADIUS*cnst::RADIUS;		
	const double t18 = 1.0/cnst::RADIUS;		

	const double friction = 1.0e-5; // friction

    for(size_t i = 0;i < mesh.nodes.size();i++) {
		const MeshNode& n = mesh.nodes[i];
		NodeDataInteraction& dt = data_interaction[i];
		
	    const double t6 = sin((n.lambda - lmbd0)*t4);		
		const double t7 = cos((n.phi - phi0)*t5);
		const double t8 = cos((n.lambda - lmbd0)*t4);
		const double t9 = sin((n.phi - phi0)*t5);
		const double t10 = sin(n.phi);
		const double t11 = cos(n.phi);						

		const double t15 = t7*t4/n.depth;
		const double t16 = (t12 + t13)*t8/(t3*t12*t13);			
				
		dt.w1 = -400000.0*t6*t15/(9.0*t3*t2)
			  + 200000.0*cnst::OMEGA*t11*t14*t8*t7*t5/(3.0*t10*n.depth)
			  - 100000.0*cnst::G*(1/t12 + 1/t13)*t6*t4*t7/(t3*t17*t10*t10)
			  + 100000.0*friction*t14*t6*t15/3.0;	
		
		dt.w2 = -400000.0*t8*t9*t5/(t10*9.0*t3*t2*n.depth)
			  - 200000.0*cnst::OMEGA*t11*t14*t6*t7/(n.depth*t4*3.0)
			  - 100000.0*cnst::G*t18*(t16*t9*t5*t18/t10 + t16*t7*t18*t11/(t10*t10))
			  + 100000.0*friction*t14*t8*t9*t5/(t10*n.depth*3.0);		

		dt.w3 = 0.0;
	}		
}
