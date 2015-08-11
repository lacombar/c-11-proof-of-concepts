#include "functor_.hh"

void
test(cb_t fn, void *arg)
{
	for (auto i = 0; i < 1000000; i++)
		for (auto j = 0; j < 1000; j++)
		{
			fn(arg);
		}
}

void
test(std::function<void(void)> f)
{
	for (auto i = 0; i < 1000000; i++)
		for (auto j = 0; j < 1000; j++)
		{
			f();
		}
}

