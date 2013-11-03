#pragma once

#include "fragmentedprogram.h"
#include "meshfragment.h"
#include "meshblockfragment.h"
#include "data.h"
#include "dfarray2d.h"
#include "dfdistributedarray2d.h"
#include "blockdistribution2d.h"
#include "doublingdistribution2d.h"

typedef DFDistributedArray2D<MeshBlockFragment> MeshArray; // regular mesh - fragmented in regular blocks
typedef DFDistributedArray2D<Data> DataArray;
typedef DFDistributedArray2D<DataCoef> DataCoefArray;
typedef DFDistributedArray2D<DataInteraction> DataInteractionArray;

/*
* Program for our Shallow Water FEM program
*/
class SHFEMProgram: public FragmentedProgram {
private:
	DoublingDistribution2D mesh_fragmentation; // block fragmentation of mesh
	BlockDistribution2D mesh_distribution; // distribution of mesh fragments by nodes

	int this_node;
	int num_of_nodes;

private:		
	void sendUpdates(DataArray& data, DataArray& left, DataArray& right, DataArray& top, DataArray& bottom);
	void recvUpdates(DataArray& data, DataArray& left, DataArray& right, DataArray& top, DataArray& bottom);
	
public:
	SHFEMProgram(IRuntimeSystem* s, const size_t& mesh_size_x, const size_t& mesh_size_y, const size_t& fragment_num_x, const size_t& fragment_num_y);
	~SHFEMProgram() {}

	void exec(const size_t& num_of_steps);
};
