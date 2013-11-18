#include "tester.h"
#include <sstream>

int main(int argc, char **argv) {

	TestConfig config(argc, argv);

	Tester(config).run(argc, argv);

	return 0;
}
