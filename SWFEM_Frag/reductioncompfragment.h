#pragma once

#include "compfragment.h"

class ReductionCompFragment : public CompFragment {
private:
	unsigned int red_id;

public:
	ReductionCompFragment() : red_id(0) {}
	virtual ~ReductionCompFragment() {}

	void setReductionId(unsigned int red_id) {
		this->red_id = red_id;
	}

	unsigned int getReductionId() const {
		return red_id;
	}	

	bool isReductionCF() const {
		return true;
	}

	virtual CompFragment::Type getType() const {
		return CompFragment::REDUCTION;
	}
	
	virtual double getReductionValue() const = 0;
};

typedef std::vector<ReductionCompFragment*> ReductionCompFragmentPtrArray;
