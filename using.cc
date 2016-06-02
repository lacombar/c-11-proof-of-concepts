#include "common.h"

struct Foo
{
	Foo()
	{
		std::cout << __func__ << std::endl;
	}
};

struct foo : public Foo
{
	foo()
	{
		std::cout << __func__ << std::endl;
	}
};

TEST(using, foo)
{
	foo f;
}
