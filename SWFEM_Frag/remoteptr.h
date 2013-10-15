#pragma once

class RemotePtr {
private:
	unsigned int id;
	void *ptr;

public:
	RemotePtr(unsigned int i) : id(i), ptr(0) {}
	RemotePtr(unsigned int i, void *p) : id(i), ptr(p) {}
	RemotePtr(const RemotePtr& p) : id(p.getId()), ptr(p.getPtr()) {}
	~RemotePtr() {}

	void setPtr(void *ptr) {
		this->ptr = ptr;
	}

	void* getPtr() const {
		return ptr;
	}

	unsigned int getId() const {
		return id;
	}
};
