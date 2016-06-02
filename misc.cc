#include "common.h"

struct A
{
	int a;
	int b;
};

void
a(const A& au = A())
{
}

TEST(misc, const_default_ref)
{
	a();
}


struct B
{
	virtual ~B() = default;
};

struct B0 : public B
{
};

TEST(misc, bar)
{
	B0 b;
}

TEST(misc, bitfield)
{
	std::vector<bool> v;

	v.resize(42);

	std::fill(v.begin(), v.end(), false);

	v[0] = false;
	v[1] = false;
	v[2] = false;
	v[3] = false;

	auto r = std::find(v.begin(), v.end(), true);

	if (r == std::end(v)) { std::cout << "bla" << std::endl; }

	std::cout << v.size() << std::endl;
	std::cout << std::distance(v.begin(), r) << std::endl;
}

struct C
{
	C * getThis() const { return nullptr; }

	int i;
};

TEST(misc, const_shit)
{
	C c;

	C* cp0 = &c;
	cp0->i = 0;

	C* const cp1 = &c;
	cp1->i = 0;

//	const C* cp2 = &c;
//	cp2->i = 0;

	auto ip = c.getThis();
	std::cout << typeid(ip).name() << std::endl;

}
