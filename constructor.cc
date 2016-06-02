#include "common.h"

#if 0
std::stringstream&&
b()
{
	return std::move(std::stringstream());
}

template<int i>
std::stringstream&&
b()
{
	const auto& ss = std::move(b());

	return std::move(ss);
}

struct A
{
	A(std::stringstream& ss) {
		std::cout << ss.str() << std::endl;
	};
};

std::stringstream&&
stringstream_generator()
{
	return std::move(std::stringstream());
}


template<typename T, typename ... Args>
std::stringstream&&
stringstream_generator(T v, Args... args)
{
	std::stringstream ss;

	ss << v;
	ss << std::move(stringstream_generator(args...)).str();

	return std::move(ss);
}



TEST(constructor, ostream_arg)
{
	//A a(b<1>());
	//A a0([](){ std::stringstream ss; ss << "foo" << "bar"; return std::move(ss);}());

	//A a1(stringstream_generator("foo", "bar"));
	A a2(static_cast<std::stringstream&>(std::stringstream() << "foo" << "bar"));

}
#endif


#define TRACE()		std::cout << __func__ << std::endl

struct B
{
	B()
	{
		TRACE();
	}

	~B()
	{
		TRACE();
	}
};

TEST(constructor, delete_void_pointer)
{
	B* b = new B;

	void *p = (void *)b;

	delete b;

}

#if 0
struct D;

struct C
{
	class Key {
		friend D;
		Key() {}
	};

	C() {}
	C(const D&& d, const Key&) {}
};

struct D
{
	std::shared_ptr<C> getC()
	{
		return std::make_shared<C>(std::move(*this), C::Key());
	}
};

TEST(constructor, hidden_relationshing)
{
	C c;
	D d;


	auto c1(std::move(d), C::Key());

	auto c0 = d.getC();


}
#endif

struct E {
	int a;
	struct c {
		int a;
	};
};

struct F {
	F() : e() {}

	E e;
};

#include <new>

TEST(constructor, placement_constructor)
{
	uint8_t buf[42];

	memset(&buf, 0xff, sizeof(buf));

	F* f = new ((void *)&buf) F();

	std::cout << f->e.a << std::endl;
}
