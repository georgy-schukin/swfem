#include "datafragment.h"
#include "compfragment.h"

CompFragment* DataFragment::moveToNextCF() {
	if (isReady()) {
		DataFragmentRoute::RoutePoint next_point = getRoute().getNextPoint();
		current_cf = next_point.getCF();
		is_locked = true;
		return current_cf;
	}
	return 0;
}

void DataFragment::freeFromCF() {
	current_cf = 0;
	is_locked = false;
}
