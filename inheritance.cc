#include "common.h"

struct Foo
{
	virtual ~Foo() = default;

	virtual void bar() { std::cout << "Foo::bar()" << std::endl; };

	void baz() { bar(); };
};

struct Fuu final : public Foo
{
	Fuu() : i(5) {};

	~Fuu() { std::cout << "Fuu::~Fuu" << std::endl; }

	void bar() { std::cout << "Fuu::bar() " << this->i << std::endl; };

	int i;
};

TEST(inheritance, foo)
{
	Fuu fuu;

	Foo& foo = fuu;

	foo.bar();

	foo.baz();
}


TEST(inheritance, fuu)
{

	std::shared_ptr<Foo> foo = std::make_shared<Fuu>();

	{
		std::shared_ptr<Foo> foo2 = std::move(foo);
	}

	std::cout << "==" << std::endl;
}

struct IA
{
	virtual ~IA() = default;

	virtual void foo() = 0;
};

struct A : virtual public IA
{
	void foo() { std::cout << typeid(*this).name() << std::endl; }
};

struct IB : virtual public IA
{
	virtual ~IB() = default;

	virtual void bar() = 0;
};

struct B : public A, public IB
{
	void bar() { std::cout << typeid(*this).name() << std::endl; }
};

TEST(inheritance, diamond)
{
	A a;

	a.foo();

	B b;

	b.foo();
	b.bar();
}
