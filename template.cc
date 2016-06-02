#include "common.h"

#if __cplusplus < 201402L
namespace std {
	template<bool B, class T = void>
	using enable_if_t = typename enable_if<B,T>::type;
}
#endif

class Base
{
};

template<typename T = void, typename Enable = void>
class A : public Base {
public:
	A(int val) : val(val) {}
	T val;
};

template<typename T>
class A<T, typename std::enable_if_t<std::is_void<T>::value>> : public Base
{
};

template<typename T = void, typename Enable = void>
class B : public A<T>
{
public:
	B(int val) :
	A<T>(val)
	{
	}
};

template<typename T>
class B<T, typename std::enable_if_t<std::is_void<T>::value>> : public A<T>
{
};

TEST(template, foo)
{
	B<> b0;
	B<int> b1(42);

	(void) b0;
}

void
f(int i)
{
	EXPECT_TRUE(false);
}

void
f(int i, int j)
{
	EXPECT_TRUE(true);
}

template <typename... T>
void
call(T... t)
{
	f(t...);
}

TEST(template, bar)
{
	call<int, int>(1, 2);
}

void
d(int a, char&& b, std::string&& c)
{
	std::cout << c << std::endl;
}

template <typename... Args>
void d_passthrough(Args&&... args)
{
	d(1, std::forward<Args>(args)...);
}

TEST(template, variadic_template_and_perfect_forwarding)
{
	std::string s("test2");

	d_passthrough('\0', "test");
	d_passthrough('\0', std::move(s));
}

template<int value>
typename std::enable_if<value == 1, bool>::type
fn()
{
	return true;
}

template<int value>
typename std::enable_if<value == 2, bool>::type
fn()
{
	return false;
}


template<int value>
inline typename std::enable_if<value == 3, bool>::type
fn()
{
	return false;
}


TEST(template, function_enablement)
{
	std::cout << fn<1>() << std::endl;
	std::cout << fn<2>() << std::endl;
	std::cout << fn<3>() << std::endl;
}


struct C
{
	C(std::ostream& os)
	{
		auto ss = static_cast<std::stringstream&&>(os);

		std::cout << ss.str() << std::endl;
	}
};

TEST(template, function_enablement_)
{
	C c(std::stringstream() << "foo" << "bar");
}

template <typename T>
struct D
{
	struct D1 {};

	virtual void enable(void) = 0;

	friend std::ostream& operator<<(std::ostream&os, const T&) { os << __func__; return os; };
};

struct E : public D<E>
{
	void enable(void) { std::cout << "oeu" << std::endl; }
};

TEST(template, stream_self_ref)
{
	E e;

	e.enable();

	std::cout << e << std::endl;
}

template <typename T>
struct F
{
};

template <template <typename> class T, typename U>
struct G
{
	T<U> f;
};

TEST(template, template_template)
{
	G<F, int> g;
}

template <typename T, typename U>
T*
foo_cast(U u)
{
	return nullptr;
}

TEST(template, partial_foo)
{
	int i;
	double d;

	auto p = foo_cast<int>(d);

	EXPECT_EQ(typeid(p).hash_code(), typeid(int*).hash_code());
}
