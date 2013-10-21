#include "cfjacobyreduce.h"
#include <math.h>

double CFJacobyReduce::exec(MeshFragment& mesh, Data& data_new, Data& data, Data& data_diag) {
	double err = 0;	
	double residial = 0;
	double residial_max = 0;		

	err_max = 0;

	for(size_t i = 0;i < data_new.size();i++) {
		NodeData& dnew = data_new[i];
		const NodeData& dt = data[i];
		const NodeData& diag = data_diag[i];

		if(fabs(dnew.u) > fabs(residial_max)) residial_max = fabs(dnew.u);
		residial = dnew.u/diag.u;
		dnew.u = dt.u - residial;
		err = fabs(dnew.u - dt.u);
		if(err > err_max) err_max = err;		

		if(fabs(dnew.v) > fabs(residial_max)) residial_max = fabs(dnew.v);
		residial = dnew.v/diag.v;
		dnew.v = dt.v - residial;
		err = fabs(dnew.v - dt.v);
		if(err > err_max) err_max = err;		

		if(fabs(dnew.xi) > fabs(residial_max)) residial_max = fabs(dnew.xi);
		residial = dnew.xi/diag.xi;
		dnew.xi = dt.xi - residial;
		err = fabs(dnew.xi - dt.xi);
		if(err > err_max) err_max = err;
	}		
	return err_max;
}
