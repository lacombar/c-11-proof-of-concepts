#include "common.h"

struct A
{
	A() { std::cout << __func__ << std::endl; }
	~A() { std::cout << __func__ << std::endl; }

	A(A const&) = delete;
	A& operator=(A const&) = delete;

	A(A&&) = default;
	A& operator=(A&&) = default;
};

std::packaged_task<void(void)>
getLambdaA()
{
	A a;

	return std::packaged_task<void(void)>([a = std::move(a)](){});
}

TEST(lambda, test_lifetime)
{
	auto fn = getLambdaA();

	std::cout << "__barrier__" << std::endl;

	fn();
}

TEST(lambda, move)
{
	auto l0 = [](){};
	__attribute__((unused)) auto l1 = std::move(l0);
}

auto
getLambdaB()
{
	A a;

	return [a = std::move(a)](){};
}

TEST(lambda, auto_return)
{
	__attribute__((unused)) auto l = getLambdaB();

	l();

	std::cout << typeid(l).name() << std::endl;
}

struct B
{
	template <typename T>
	B(T t) { };

private:
	template <typename T>
	struct internal
	{
		internal(T t) { };

		T t;
	};
};

TEST(lambda, erasure)
{
	B b(1);
}

template <typename T>
struct C
{
	C(T t) : t(t) {}
	C(C<T>&& c) : t(std::move(c.t)) {}

	C& operator=(C<T>&& c) { this.t = c.t; return *this; }

	T t;
};

TEST(lambda, template_parameter_type)
{
	auto l0 = [](){};
	auto l1 = [](){};

	C<decltype(l0)> c00(l0), c01(std::move(c00));
	C<decltype(l1)> c1(l1);

//	c1 = std::move(c01);

	(void)c00;
	(void)c01;
	(void)c1;
}

template <typename T>
struct D
{
	T t;

	template <typename Handler>
	void foo(Handler h)
	{
		h();
	}
};

TEST(lambda, template_method)
{
	D<int> d;

	d.foo([](){ std::cout << "FTW!" << std::endl; });
}

