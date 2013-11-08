#include "datafragment.h"
#include "compfragment.h"

CompFragment* DataFragment::moveToNextCF() {
	if (!current_cf || current_cf->isReady()) {
		current_cf = shiftToNextCF();
		return current_cf;
	} else
		return 0;
}

CompFragment* DataFragment::moveToNextCFInTheSameGroup() {
	if (!current_cf || current_cf->isReady()) {
		current_cf = shiftToNextCFInTheSameGroup();
		return current_cf;
	} else
		return 0;
}

CompFragment* DataFragment::shiftToNextCF() {
	if (!getRoute().isEmpty()) {
		DataFragmentRoute::RoutePoint next_point = getRoute().getNextPoint();
		CompFragment *cf = next_point.getCF();
		cf->pushArg(this);
		//setCurrentGroup(cf->getGroupId());
		//lock();
		return cf;
	}
	return 0;
}

CompFragment* DataFragment::shiftToNextCFInTheSameGroup() {
	if (!getRoute().isEmpty()) {
		if ((getCurrentGroup() == DataFragment::NO_GROUP) ||
			(getCurrentGroup() == getRoute().peekNextCF()->getGroupId())) {			
			DataFragmentRoute::RoutePoint next_point = getRoute().getNextPoint();
			CompFragment *cf = next_point.getCF();
			cf->pushArg(this);
			setCurrentGroup(cf->getGroupId());
			//lock();
			return cf;
		}
	}
	return 0;
}

void DataFragment::freeFromCF() {
//	unlock();
	setCurrentGroup(DataFragment::NO_GROUP);
//	current_cf = 0;
}
