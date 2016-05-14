#include "functor_.hh"

#define OUTER 1000 * 1000
#define INNER 10000

void
test(cb_pair_t cb_pair)
{
	for (auto i = 0; i < OUTER; i++)
		for (auto j = 0; j < INNER; j++)
		{
			cb_pair.first(cb_pair.second);
		}
}

void
test(cb_t fn, void *arg)
{
	for (auto i = 0; i < OUTER; i++)
		for (auto j = 0; j < INNER; j++)
		{
			fn(arg);
		}
}

void
test(std::function<void(void)> f)
{
	for (auto i = 0; i < OUTER; i++)
		for (auto j = 0; j < INNER; j++)
		{
			f();
		}
}

