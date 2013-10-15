#pragma once

#include "remoteptr.h"
#include "datafragment.h"
#include <vector>
#include <string>
#include <set>

/**
* Generic computing fragment
*/
class CompFragment {
public:
	enum Type {
		SIMPLE = 0,
		REDUCTION
	};

private:	
	std::vector<DataFragment*> args;
	unsigned int ready_cnt;
	//unsigned int group_id;
	bool is_done;

protected:
	void addArg(DataFragment *arg);

public:
	bool pushArgAndCheckReady(DataFragment *arg);
	bool isReady() const;

public:	
	CompFragment() : ready_cnt(0), is_done(false) {}
	
	const std::vector<DataFragment*>& getArgs() const {
		return args;
	}

	template<class T> T& getArg(const unsigned int& num) const {
		return *(T*)(args[num]);
	}

	/*void setGroupId(const unsigned int& group_id) {
		this->group_id = group_id;
	}

	unsigned int getGroupId() const {
		return group_id;
	}*/

	void setDone() {
		this->is_done = true;
	}

	bool isDone() const {
		return is_done;
	}
	
	virtual bool isReductionCF() const {
		return false;
	}

	virtual CompFragment::Type getType() const {
		return CompFragment::SIMPLE;
	}

	/*virtual bool isEventCF() const {
		return false;
	}*/

	virtual ~CompFragment() {}

	virtual void execute() = 0;
	virtual std::string toString() const;	
};

typedef std::vector<CompFragment*> CompFragmentPtrArray;
