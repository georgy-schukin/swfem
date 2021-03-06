#include "shfemseqprogram.h"
#include "cfshfem.h"
#include "meshfragment.h"
#include "data.h"
#include "cnst.h"
#include <iostream>

using namespace std;

/*
* Sequental program, without fragments
*/
void SHFEMSeqProgram::exec(const size_t& mesh_size_x, const size_t& mesh_size_y, const size_t& num_of_steps) {
	const double bx = 0.0;
	const double by = 90.0;	
	const double sx = (10.0 - bx)/(mesh_size_x - 1);
	const double sy = (100.0 - by)/(mesh_size_y - 1);

	MeshBlockFragment mesh;
	Data data, data_new, data_prev, data_diag, data_exact;	
	DataCoef data_coef;	
	DataInteraction data_interaction;

	CFGen(bx, by, sx, sy, mesh_size_x, mesh_size_y, 0, 0, mesh_size_x, mesh_size_y).exec(mesh);		

	CFAlloc().exec(mesh, data, data_new, data_prev, data_diag, data_exact, data_coef, data_interaction);

	CFInit().exec(mesh, data, data_coef);	
	CFExact(0).exec(mesh, data);
	CFExact(0).exec(mesh, data_exact);
	CFCoef().exec(mesh, data_coef);		
	
	for (size_t s = 1; s <= num_of_steps; s++) {		
		cout << "Time step: " << s << endl;

		CFInteraction(s*cnst::TAU).exec(mesh, data_interaction);		
		CFDiag().exec(mesh, data_coef, data_interaction);
		CFJacobyDiag().exec(mesh, data_diag, data_coef);
		CFCopy().exec(data_prev, data);		

		double eps = 1.0;
		while (eps > cnst::EPS) {	// Jacoby method
			CFJacobyMultDirect().exec(mesh, data_new, data, data_prev, data_coef);									
			eps = CFJacobyReduce().exec(mesh, data_new, data, data_diag);				
			CFCopy().exec(data, data_new);
			cout << "EPS: " << eps << endl;
		}				
	}
}
