#pragma once

#include "compfragment.h"

class ReductionCompFragment : public CompFragment {
private:
	size_t reduction_id;

public:
	ReductionCompFragment() : reduction_id(0) {}
	virtual ~ReductionCompFragment() {}

	void setReductionId(size_t reduction_id) {
		this->reduction_id = reduction_id;
	}

	size_t getReductionId() const {
		return reduction_id;
	}	

	/*bool isReductionCF() const {
		return true;
	}*/

	virtual CompFragment::Type getType() const {
		return CompFragment::REDUCTION;
	}
	
	virtual double getReductionValue() const = 0;
};

typedef std::vector<ReductionCompFragment*> ReductionCompFragmentPtrArray;
