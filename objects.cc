#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

struct __int
{
	int val;
};

class C
{
public:
	C() : i({42})
	{
		std::cout << "C()" << std::endl;
	}

	~C()
	{
		std::cout << "~C()" << std::endl;
	}

#if 0
	C(const C&)
	{
		std::cout << "C(const C&)" << std::endl;
	}
#endif
	C(const C&) = delete;

	/*
	C& operator= (C& c)
	{
		std::cout << "C& operator= (C& c)" << std::endl;
		return *this;
	}
	*/

	C& operator= (const C& c)
	{
		std::cout << "C& operator= (const C& c)" << std::endl;
		return *this;
	}

	/*
	C& operator= (C&& c)
	{
		std::cout << "C& operator= (C&& c)" << std::endl;
		return *this;
	}
	*/

	operator __int&& ()
	{
		std::cout << "__int" << std::endl;
		return std::move(this->i);
	}

	operator __int* ()
	{
		return &i;
	}

	__int i;
};

#if 0
#include <functional>

TEST(objects, foo)
{
	C c0, c1;

	c0 = c1;

	[] (C& c) { C c0; c0 = c; } (c0);

	__int i = std::move(c0);

	__int *ip = *(&c0);
	ip->val = 43;

	std::cout << i.val << c0.i.val << std::endl;
}
#endif

class D
{
public:
	D() : called(false) {}
	virtual void f() {}
	operator bool() { return called; }
private:
	bool called;
};

class E : public D
{
public:
	E() : called(false) {}
	virtual void f() { called = true; }
	operator bool() { return called; }
private:
	bool called;
};

class F : public E
{
public:
	F() : called(false) {}
	virtual void f()
	{
		called = true;
		E::f();
	}
	operator bool() { return called; }
private:
	bool called;
};

TEST(objects, super_call_chain)
{
	F f;

	f.f();

	ASSERT_EQ((bool)f, true);
	ASSERT_EQ((bool)(*static_cast<E*>(&f)), true);
}

class G
{
public:
	G(int i) : i(i) {}
	int fn()
	{
		return i;
	}

	G(const G&) = delete;
	G& operator= (const G&) = delete;

	G(G&&) = default;
	G& operator= (G &&) = default;
private:
	int i;
};

class H : public G
{
public:
	H() : G(0)
	{
	}

	H(G&& g) : G(std::move(g))
	{
	}
};

TEST(objects, move)
{
	G g(42);

	H h(std::move(g));

	ASSERT_EQ(dynamic_cast<G*>(&h)->fn(), 42);

	try {
		return;
		std::cout << "bla;" << std::endl;
	} catch (...) { }
	std::cout << "bla;" << std::endl;
}

class I
{
public:
#if 0
	I(const I&) = delete;
	I& operator=(const I&&) = delete;

	I(I&&) = default;
	I& operator=(I&&) = default;
#endif
	I(I&&) = default;
	I& operator=(I&&) = default;

private:
	I(const I&) = delete;
	I& operator=(const I&&) = delete;

};

#include <type_traits>

TEST(objects, properties)
{

	ASSERT_EQ(std::is_copy_constructible<I>::value, false);
	ASSERT_EQ(std::is_copy_assignable<I>::value, false);
	ASSERT_EQ(std::is_move_constructible<I>::value, true);
	ASSERT_EQ(std::is_move_assignable<I>::value, true);
}

class J
{
};

class K : public J
{
};

TEST(objects, move_cont)
{
	J j;
	K k;

	std::vector<J> vec;

	vec.push_back(std::move(k));

	J j0 = std::move(vec[0]);


}

struct L
{
	operator uint8_t*()
	{
		std::cout << "L" << std::endl;
		return nullptr;
	}
};

struct M : public L
{
	operator uint8_t*()
	{
		std::cout << "M" << std::endl;
		return *reinterpret_cast<L*>(this);
	}
};

struct N
{
	int val;
};

#include <functional>

struct O1
{
	virtual void fn() = 0;
};

struct O2 : public O1
{
	virtual void fn()
	{
		std::cout << "foo" << std::endl;
	}
};

TEST(objects, overload)
{
	O2 o2;

	auto f0 = [] (O1 *o) { o->fn(); };
	//auto f1 = [] (O1 o) { o->fn(); };

	f0(&o2);
}

struct moveable_noncopyable
{
	moveable_noncopyable() { }

	moveable_noncopyable(const moveable_noncopyable&) = delete;
	moveable_noncopyable& operator= (const moveable_noncopyable&) = delete;

	moveable_noncopyable(moveable_noncopyable&&) = default;
	moveable_noncopyable& operator= (moveable_noncopyable&&) = default;
};

class Q0 // IBase
{
public:
	Q0() {}
	Q0(int i) : i(i) {}
	virtual void foo() = 0;

	int i;
};

bool Q1_foo_called = false;
class Q1 : public moveable_noncopyable,
	public virtual Q0 // Base
{
public:
	Q1(int i) : i(i) { }
	virtual void foo() { Q1_foo_called = true; };
private:
	FRIEND_TEST(objects, diamond_virtual_inheritance);
	int i;
};

class Q2 : public virtual Q0 // IDerived
{
public:
	Q2() {}
	virtual void bar() = 0;
};

bool Q3_bar_called = false;
class Q3 : public Q1, public Q2 // Derived
{
public:
	Q3(int i) : Q1(i) {}
	virtual void bar() { Q3_bar_called = true; };
};

class Q4 : public Q3
{
public:
	Q4(int i) : Q3(i) {}
};

TEST(objects, diamond_virtual_inheritance)
{
	Q4 q4(42);

	ASSERT_FALSE(Q1_foo_called);
	q4.foo();
	ASSERT_TRUE(Q1_foo_called);

	ASSERT_FALSE(Q3_bar_called);
	q4.bar();
	ASSERT_TRUE(Q3_bar_called);

	ASSERT_EQ(q4.i, 42);
}

struct R0
{
};

struct R1 : public R0
{
};

TEST(objects, move_construct)
{
	R1 r1;

	R0 r0(std::move(r1));
}

class S0
{
public:
	virtual int foo(std::unique_ptr<int>) = 0;
};

class S1 : public S0
{
public:
	MOCK_METHOD1(foo, int(std::unique_ptr<int>));
};

TEST(objects, googlemock_function_with_rvalue_parameter)
{
	S1 s1;

	EXPECT_CALL(s1, foo(testing::NotNull())).WillRepeatedly(testing::Return(42));

	std::unique_ptr<int> p(new int);
	int ret = s1.foo(std::move(p));

	ASSERT_EQ(ret, 42);
}

struct T1;

struct T0
{
	T0(int i) : i(i)
	{
	}
	T0(T1&& t1)
	{
		T0::T0(reinterpret_cast<T0&&>(std::move(t1)));
	}
	int i;
};

struct T1 : public T0
{
	T1(int i, int j) : T0(i), j(j)
	{
	}
	int j;
};

TEST(objects, custom_move_to_base_class)
{
	T1 t1(21, 42);

	T0 t0(std::move(t1));

	ASSERT_EQ(t1.i, 21);
	ASSERT_EQ(t0.i, 21);
}

struct U0
{
	virtual ~U0()
	{
		std::cout << __func__ << std::endl;
	}
};

struct U1 : public U0
{
	~U1()
	{
		std::cout << __func__ << std::endl;
	}
};

TEST(objects, destruction_order)
{
	U1 u1;
}

struct V0
{
	V0(int i)
	{
		std::cout << i << std::endl;
	}
	V0() :
		V0(1)
	{
		std::cout << __func__ << std::endl;
	}
};

TEST(objects, delegatingConstructor)
{
	V0 v0;
}

class W0
{
public:
	W0() :
		W0(1)
	{
	}
private:
	W0(int i)
	{
		std::cout << "private" << std::endl;
	}
};

TEST(objects, delegatingConstructorPrivate)
{
	W0 w0;
}

class X0
{
public:
	X0()
	{
		std::cout << __func__ << std::endl;
	}

	~X0()
	{
		std::cout << __func__ << std::endl;
	}
};

TEST(objects, testAssignmentOperator)
{
	X0 x0, x1;

	x0 = std::move(x1);
	std::cout << "===" << std::endl;
}
