#pragma once

#include "testconfig.h"

class Tester {
protected:
	TestConfig config;

public:
	Tester(const TestConfig& conf) : config(conf) {}
	~Tester() {}

	void run(int argc, char **argv);
};
