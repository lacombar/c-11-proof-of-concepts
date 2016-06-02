#include "common.h"

#include <limits>

int foo(int len)
{
}

TEST(limits, generic_numeric_limits)
{
	uint16_t ushort;

	std::cout << std::numeric_limits<uint16_t>::max() << std::endl;

	std::cout << std::numeric_limits<decltype(ushort)>::max() << std::endl;
}
