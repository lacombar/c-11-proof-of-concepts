#include <iostream>
#include <memory>

#include <gtest/gtest.h>

TEST(unique_ptr, test_reset) {
	std::unique_ptr<int> p(new int);

	p.reset();

	ASSERT_EQ(p.get(), nullptr);
}

class Foo {
public:
	Foo() { __constructed++; };
	~Foo() { __destroyed++; }

	static int __constructed;
	static int __destroyed;
};

int Foo::__constructed = 0;
int Foo::__destroyed = 0;

static inline int Foo_leaked()
{
	return Foo::__constructed - Foo::__destroyed;
}

#if 0
/* Need to be ran with:
 *
 * MALLOC_CHECK_=0
 *
 * Setting it internally won't do the trick.
 */
TEST(unique_ptr, smart_pointer_sync_no_object_leak)
{
	{
		std::unique_ptr<Foo[]> f(new Foo[2]);
	}

	ASSERT_EQ(Foo_leaked(), 0);
}

TEST(unique_ptr, smart_pointer_mismatch_leak)
{
	{
		std::unique_ptr<Foo> f(new Foo[2]);
	}

	ASSERT_EQ(Foo_leaked(), 1);
}
#endif

TEST(unique_ptr, smart_pointer_sync_no_type_leak)
{
	{
		std::unique_ptr<int> f(new int[256]);
	}
}

class A
{
public:
	A()
	{
		std::cout << __func__ << std::endl;
	}

	~A()
	{
		std::cout << __func__ << std::endl;
	}
};

struct nop
{
	template <typename T>
	void operator() (T const &) const noexcept { }
};

TEST(unique_ptr, testFoo)
{
	std::unique_ptr<A, nop> a;

	std::cout << sizeof(std::unique_ptr<A>) << std::endl;
}
