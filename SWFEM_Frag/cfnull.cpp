#include "cfnull.h"
#include <boost/foreach.hpp>

void CFNull::exec(Data& data) {
	BOOST_FOREACH(NodeData& dt, data) {
		dt.u = 0.0;
		dt.v = 0.0;
		dt.xi = 0.0;
	}
}