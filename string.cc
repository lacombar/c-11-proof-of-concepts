#include "common.h"

enum class E0
{
	FOO,
	BAR
};


#if 0
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
#endif

TEST(string, netmask)
{
	std::string s = "10.0.0.0/16";

	auto sep = s.find("/");
	if (sep != std::string::npos)
	{
		std::string mask = s.substr(sep + 1);
		s = s.substr(0, sep);
		std::cout << mask << std::endl;
	}

	std::cout << s << std::endl;


	uint8_t * i, j;

	std::cout << sizeof i << std::endl;
	std::cout << sizeof j << std::endl;


	std::cout << "foo" + std::to_string(32) << "x" << std::endl;
}
