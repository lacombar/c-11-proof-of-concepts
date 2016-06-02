#include "common.h"

void
a(const std::string& s)
{
	std::cout << s << std::endl;
}

class A
{
public:
	template <typename T>
	A(T&& s)
	{
		a(s);
	}
};


struct b
{
	struct _inner {
		int i;
	};
};

TEST(rvalue, string)
{
	struct b b0 { 0 };
	std::string s("foo");

	A a0(s);
	A a1("bar");
}

