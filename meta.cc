#include <iostream>
#include <functional>

#include "splitlaptimer.hh"

class Foo
{
public:
	virtual ~Foo() {};
};

template <typename IN, typename OUT = bool>
class Bar : public Foo
{
public:
	Bar(IN in) : in(in) { };
	IN in;
	OUT out;

};

template <typename IN, typename OUT = bool>
class Baz : public Bar<IN, OUT>
{
	public:
	Baz(IN in) : Bar<IN, OUT>(in) { };
	int dummy() { return 1; };
};


void baz_dynamic(Foo *f)
{
	Baz<int, bool> *b = dynamic_cast<Baz<int, bool> *>(f);
	volatile int res = b->dummy();
}

void baz_reinterpret(Foo *f)
{
	Baz<int, bool> *b = reinterpret_cast<Baz<int, bool> *>(f);
	volatile int res = b->dummy();
}

void
RUN_TEST(std::string name,
	std::function<void(void)> f,
	size_t ntest = 20,
	size_t niter = 1000000)
{
	SplitLapTimer s;

	s.start(name);

	for (auto i = 0; i < ntest; i++)
	{
		for (auto j = 0; j < niter; j++)
		{
			f();
		}
		s.split();
	}

	std::cout << s << std::endl;
}

int main(int argc, char *argv[])
{
	Baz<int> b0(42);

	RUN_TEST("dynamic_cast<>()", [&] () { baz_dynamic(&b0); });

	RUN_TEST("reinterpret_cast<>()", [&] () { baz_reinterpret(&b0); });

	return 0;
}
