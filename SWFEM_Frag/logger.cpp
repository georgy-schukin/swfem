#include "logger.h"
#include <iostream>
#include <sstream>
#include <boost/foreach.hpp>

/*void Logger::onCFDone(CompFragment *cf) {
	ostringstream out;
	out << "Done " << cf->toString() << endl;
	cout << out.str();
}*/

void Logger::onCFsDone(CompFragmentBunch& cfs) {		
	std::ostringstream out;	
	BOOST_FOREACH(CompFragment *cf, cfs)
		out << "Done " << cf->toString() << std::endl;
	std::cout << out.str();
}
