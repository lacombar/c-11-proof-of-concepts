#include <type_traits>

#include <gtest/gtest.h>

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
