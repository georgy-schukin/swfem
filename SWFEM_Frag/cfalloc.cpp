#include "cfalloc.h"

void CFAlloc::exec(MeshBlockFragment& mesh, Data& data, Data& data_new, Data& data_prev, Data& data_diag, Data& data_exact, 
	DataCoef& data_coef, DataInteraction& data_interaction) {

	const size_t data_size = mesh.getSizeByX()*mesh.getSizeByY();

	data.resize(data_size);
	data_new.resize(data_size);
	data_prev.resize(data_size);
	data_diag.resize(data_size);
	data_exact.resize(data_size);
	data_coef.resize(data_size);
	data_interaction.resize(data_size);
}