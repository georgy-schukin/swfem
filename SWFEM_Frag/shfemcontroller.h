#pragma once

#include "fpcontroller.h"
#include "mesh.h"
#include "data.h"
#include "dfarray.h"
#include "dfarray1d.h"
#include "dfarray2d.h"
#include "dfdistributedarray2d.h"
#include "distribution2d.h"
#include <vector>

/*
* Controller for our Shallow Water FEM program
*/
class SHFEMController: public FPController {
private:
	struct MeshData {
		std::vector<size_t> start_x;	// indices of first point of the mesh in fragments by X
		std::vector<size_t> start_y;	// indices of first point of the mesh in fragments by Y
		std::vector<size_t> nx;		// num of points in fragments by X
		std::vector<size_t> ny;		// num of points in fragments by Y
	};

private:
	MeshData mesh_data;
	Distribution2D mesh_distribution;

	int this_node;
	int num_of_nodes;

private:	
	void distribute(const size_t& mesh_size_x, const size_t& mesh_size_y, const size_t& fragment_num_x, const size_t& fragment_num_y, MeshData& m_data);

	void update(DFArray2D<Data>& dt, DFArray1D<Data>& st, DFArray1D<Data>& rt, DFArray1D<Data>& sb, DFArray1D<Data>& rb);		
	void outerUpdateTop(DFArray2D<Data>& dt, DFArray1D<Data>& send, DFArray1D<Data>& recv); // update top of dt
	void outerUpdateBottom(DFArray2D<Data>& dt, DFArray1D<Data>& send, DFArray1D<Data>& recv); // update bottom of dt
	void innerUpdate(DFArray2D<Data>& dt);	

	void performUpdate(DFArray& st, DFArray& rt, DFArray& sb, DFArray& rb);
	void performOuterUpdate(DFArray& send, DFArray& recv, const int& tag, const int& rank);
	
public:
	SHFEMController(IRuntimeSystem* s);
	~SHFEMController() {}

	void exec(const size_t& mesh_size_x, const size_t& mesh_size_y, const size_t& fragment_num_x, const size_t& fragment_num_y, const size_t& num_of_steps);
};
