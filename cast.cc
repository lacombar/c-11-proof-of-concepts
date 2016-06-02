#include "common.h"

TEST(cast, type)
{
	int j, i = 0;
	int& jr = j;

	j = static_cast<decltype(jr)>(i);
}
