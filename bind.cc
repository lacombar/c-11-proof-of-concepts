#include "common.h"

struct A
{
	A() {}
	~A() { std::cout << __func__ << std::endl; }
	A(const A&) = delete;
	A& operator=(const A&) = delete;
	A(const A&&) {};
};

void
f_a(A a)
{
	std::cout << __func__ << std::endl;
}

TEST(bind, move_only)
{
	std::unique_ptr<A> a = std::make_unique<A>();

	auto f = std::bind(&f_a, std::move(a));

	//f();
}

TEST(bind, move_param)
{
	A a;

	auto f = std::bind(&f_a, std::placeholders::_1);

	f(std::move(a));
}
