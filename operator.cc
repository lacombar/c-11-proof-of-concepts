#include "common.h"

//class B {};

//class X : public B {
//	public:
//	operator B&() { return *this; };
//	operator const B*() const { return nullptr; };
//};

struct __int
{
	int val;
};

class C0
{
public:
	C0(__int i) : i(i)
	{
	}

	operator __int&()
	{
		return this->i;
	}

	operator double()
	{
		return 42.0;
	}

	C0& operator= (__int&& i)
	{
		this->i = i;
		return *this;
	}
protected:
	__int i;
};

TEST(operator, test_basic_user_defined_conversion)
{
	C0 c({ 42 });

	__int i(c);

	std::cout << (double)c << std::endl;
	std::cout << static_cast<double>(c) << std::endl;

	ASSERT_EQ(i.val, 42);
}

TEST(operator, test_class_assignment)
{
	C0 c({ 42 });

	c = { 43 };

	__int i(c);

	ASSERT_EQ(i.val, 43);
}

struct __bool
{
	bool val;
};

class C1 : public C0
{
public:
	C1(__int i, __bool b) :
		C0(i),
		b(b)
	{
	}

	operator __bool()
	{
		return this->b;
	}

	C1& operator= (__int& i)
	{
		this->i = i;
		return *this;
	}

	C1& operator= (__bool&& v)
	{
		this->b = v;
		return *this;
	}
private:
	__bool b;
};

TEST(operator, foo)
{
	C1 c({ 42 }, { true });

	__int i({ 43 });
	c = i;

	c = { false };

	i = c;
	__bool b(c);

	ASSERT_EQ(i.val, 43);
	ASSERT_EQ(b.val, false);
}

struct D
{
	operator int()
	{
		return 42;
	}
private:
	int val;
};

class foo
{
	public:
    operator int()
    {
            return 5;
        }
};

TEST(operator, bar)
{
	D d;
	D* dp = &d;

	std::cout << dp->operator int() << std::endl;

	foo* a = new foo();   
	int b = a->operator int();

}

constexpr int operator"" _deg (unsigned long long deg)
{
    return deg / 10;
}

TEST(objects, user_defined_literals)
{
	std::cout << 90_deg << std::endl;
}

class E
{
public:
	E() {};

	friend std::ostream& operator<<(std::ostream& os, const E& e) { return os; };
};

TEST(operator, smart_pointer_interraction)
{
	auto e = std::make_shared<E>();

	std::cout << *e;
}


struct IF
{
public:

	virtual ~IF() = 0;

	virtual const std::string to_string() const = 0;

	friend std::ostream& operator<<(std::ostream& os, const IF& _if)
	{
		os << _if.to_string();
		return os;
	};
};

inline IF::~IF() { };

struct F : public IF
{
public:
	F() { }
	~F() { }

	const std::string to_string() const
	{
		return __func__;
	}
};

TEST(operator, base_class_smart_pointer_interraction)
{
	std::shared_ptr<IF> _if = std::make_shared<F>();

	std::cout << *_if << std::endl;
}

typedef void *g_fn_t;
void
g_fn(g_fn_t)
{
}

struct G
{
	g_fn_t operator *() { std::cout << "g_fn_t" << std::endl; return nullptr; }
};

int operator* (G, G*) { std::cout << "oaue" << std::endl; return 42; }

TEST(operator, oaeu)
{
//	auto g0 = std::make_shared<G>();
//	G* pg0 = g.get();
	//int i = *g1;
	//std::cout << i << std::endl;

	G g;

	G* g1 = &g;

	g_fn(**g1);
}
