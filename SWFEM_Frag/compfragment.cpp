#include "compfragment.h"
#include <sstream>
#include <boost/foreach.hpp>
#include <iostream>

void CompFragment::pushArg(DataFragment *arg) {
	BOOST_FOREACH(DataFragment *df, args) {
		if (df == arg)
			ready_cnt++;	
	}
	//std::cout << arg << " -> " << this->toString() << " : " << ready_cnt << " ( " << args.size() << " ) " << std::endl;
}

bool CompFragment::pushArgAndCheckReady(DataFragment *arg) {
	BOOST_FOREACH(DataFragment *df, args) {
		if (df == arg)
			ready_cnt++;
	}
	//std::cout << this->toString() << " : " << ready_cnt << " ( " << args.size() << " ) " << std::endl;
	return (ready_cnt == args.size());	
}

bool CompFragment::isReady() const {
	/*BOOST_FOREACH(const RemotePtr& p, args)
		if(!p.getPtr())
			return false;
	return true;*/
	return (ready_cnt == args.size());
}

std::string CompFragment::toString() const {
	std::ostringstream out;
	out << " (";
	for(size_t i = 0;i < args.size() - 1;i++) 
		out << args[i] << ", ";
	if(args.size() > 0)
		out << args.back();
	out << ")"; /*[" << group_id << "]";*/
return out.str();
}
