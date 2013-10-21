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
	size_t ready_cnt;
	size_t group_id;
	size_t priority;
	bool is_done;

protected:
	void addArg(DataFragment *arg);

public:
	bool pushArgAndCheckReady(DataFragment *arg);
	bool isReady() const;

public:	
	CompFragment() : ready_cnt(0), group_id(0), priority(0), is_done(false) {}
	
	const std::vector<DataFragment*>& getArgs() const {
		return args;
	}

	template<class T> T& getArg(const size_t& num) const {
		return *(T*)(args[num]);
	}

	void setGroupId(const size_t& group_id) {
		this->group_id = group_id;
	}

	size_t getGroupId() const {
		return group_id;
	}

	void setPriority(const size_t& priority) {
		this->priority = priority;
	}

	size_t getPriority() const {
		return priority;
	}

	void setDone() {
		this->is_done = true;
	}

	bool isDone() const {
		return is_done;
	}

	virtual CompFragment::Type getType() const {
		return CompFragment::SIMPLE;
	}
	
	/*virtual bool isReductionCF() const {
		return false;
	}*/	

	/*virtual bool isEventCF() const {
		return false;
	}*/

	virtual ~CompFragment() {}

	virtual void execute() = 0;
	virtual std::string toString() const;	
};

typedef std::vector<CompFragment*> CompFragmentPtrArray;
