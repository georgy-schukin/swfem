#pragma once

class RemotePtr {
private:
	size_t id;
	void *ptr;

public:
	RemotePtr(size_t i) : id(i), ptr(0) {}
	RemotePtr(size_t i, void *p) : id(i), ptr(p) {}
	RemotePtr(const RemotePtr& p) : id(p.getId()), ptr(p.getPtr()) {}
	~RemotePtr() {}

	void setPtr(void *ptr) {
		this->ptr = ptr;
	}

	void* getPtr() const {
		return ptr;
	}

	size_t getId() const {
		return id;
	}
};
