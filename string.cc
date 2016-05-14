#include <iostream>

#include <gtest/gtest.h>

enum class E0
{
	FOO,
	BAR
};


constexpr std::ostream& operator<<(std::ostream& os, E0 e0)
{
	switch (e0)
	{
	case E0::FOO:
		os << "foo";
		break;
	case E0::BAR:
		os << "bar";
		break;
	}

	return os;
}

TEST(string, foo)
{
	E0 e0 = E0::FOO;

	std::cout << e0	<< std::endl;
}
