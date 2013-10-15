#include "compfragment.h"
#include <sstream>
#include <boost/foreach.hpp>

void CompFragment::addArg(DataFragment *arg) {
	args.push_back(arg);	
}

bool CompFragment::pushArgAndCheckReady(DataFragment *arg) {
	BOOST_FOREACH(DataFragment *df, args)
		if (df == arg)
			ready_cnt++;
	//ready_cnt++;
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
	for(unsigned int i = 0;i < args.size() - 1;i++) 
		out << args[i] << ", ";
	if(args.size() > 0)
		out << args.back();
	out << ")"; /*[" << group_id << "]";*/
return out.str();
}
