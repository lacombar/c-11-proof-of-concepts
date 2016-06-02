#include "common.h"

class Base
{
public:
	virtual ~Base() {};
};

class Derived : public Base
{
public:
	virtual ~Derived() {};
};

void
fn(std::shared_ptr<Base>& p)
{
	p.reset();
}

std::shared_ptr<Base>
gn()
{
	auto p = std::make_shared<Derived>();
	return p;
}

TEST(smart_ptr, test)
{
	std::shared_ptr<Base> b0 = std::make_shared<Derived>();

#if __cplusplus >= 201402L
	std::unique_ptr<Base> b1 = std::make_unique<Derived>();
#endif

	fn(b0);

//	fn(std::make_shared<Derived>());

	auto g = gn();
}

struct C
{
	C() { std::cout << __func__ << std::endl; }
	~C() { std::cout << __func__ << std::endl; }
};

TEST(smart_ptr, forced_reset)
{

	auto c = std::make_shared<C>();

	c.reset();

	std::cout << __func__ << std::endl;
}

struct D : public std::enable_shared_from_this<D>
{
	D(int i) {}
	D() = delete;

};

TEST(smart_ptr, shared_from_this)
{
	auto d = std::make_shared<D>(1);
}

class B
{
};

void B_deleter(B* b)
{
	std::cout << __func__ << " -> " << b << std::endl;
}

TEST(shared_ptr, free_function_deleter)
{
	{
		std::shared_ptr<B> b((B*)0x42, B_deleter);
	}

	{
		std::shared_ptr<B> b(nullptr, B_deleter);
	}

	{
		std::shared_ptr<B> b(nullptr, B_deleter);

		b = std::shared_ptr<B>((B*)0x43, B_deleter);

	}
}

void free_int(int* i)
{
	delete i;
}

TEST(unique_ptr, free_function_deleter)
{
	std::unique_ptr<int, void(*)(int*)> i0(new int, free_int);
	std::unique_ptr<int> i1(new int);

	std::cout << sizeof(i0) << std::endl;
	std::cout << sizeof(i1) << std::endl;
}

#include <memory>

class E {
   public:
     static std::shared_ptr<E> Create();

   private:
     E() {}
};

std::shared_ptr<E>
E::Create()
{
	struct MakeSharedEnabler : public E {
		MakeSharedEnabler() : E()
		{
		}
	};

    return std::make_shared<MakeSharedEnabler>();
}

