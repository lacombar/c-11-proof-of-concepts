#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::Test;

template <typename T>
class C : public testing::Test
{
public:
	T value_;
};

TYPED_TEST_CASE(C, int);

TYPED_TEST(C, val)
{
	EXPECT_FALSE(true)
}

class C0
{
	public:
	C0(int i) { std::cout << __func__ << " " << i << std::endl;}
};

template <typename T>
class C : public T
{
	public:
	C() : T(42) {}
};

TEST(foo, bar)
{
	C<C0> c;
}
