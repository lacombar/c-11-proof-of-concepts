#include "common.h"

struct A
{
	A() { std::cout << "construct" << std::endl; }
	~A() { std::cout << "destruct" << std::endl; }

	A(const A& a) { std::cout << "copy construct" << std::endl; }
	A(A&& a) { std::cout << "move construct" << std::endl; }

	A& operator=(A&&) { std::cout << "move assign" << std::endl; return *this; }
	A& operator=(const A&) { std::cout << "copy assign" << std::endl; return *this; }
};

TEST(function, test)
{
/*
	std::function<void(void)> t = std::bind([](A&) { std::cout << "a" << std::endl; }, A());
	std::function<void(void)> u = std::move(t);

	std::vector<std::function<void(void)>> v;

	v.reserve(8);

	v.emplace_back(std::move(u));

	v[0]();
	v[0]();
	v[0]();
*/
	std::vector<std::function<void(int)>> v1;
	v1.reserve(8);

	std::cout << sizeof(std::function<void(void)>) << std::endl;
	memset(&v1[0], 0, 32);


	v1[0](1);
}

TEST(function, vector)
{
	std::vector<std::function<void(void)>> v;

	v.reserve(42);

	memset(&v[0], 0, v.capacity() * sizeof(std::function<void(void)>));

	std::function<void(void)> fn = [](){};


	v[0] = std::move(fn);
	v[1] = std::move(fn);
	v[2] = std::move(fn);
}
