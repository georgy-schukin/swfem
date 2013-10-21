#pragma once

#include <map>
#include <cstddef>

/**
* Defines distribution of data across nodes
*/
template <class T>
class Distribution {
private:
	std::map<size_t, T> distr;

public:
	Distribution() {}
	Distribution(const Distribution<T>& d) {
		this->distr = d.distr;
	}
	~Distribution() {}

	void set(const size_t& node, const T& elem) {
		distr[node] = elem;
	}

	const T& get(const size_t& node) const {
		return distr.at(node);
	}

	void clear() {
		distr.clear();
	}
};
