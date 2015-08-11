#include <iostream>
#include <memory>

#include "functor_.hh"

class Foo
{
public:
	static void CIface(void *);
	std::function<void(void)> get_CXXIface();
private:
	void work();
	volatile int i_;
};

void
Foo::work()
{
	i_++;
}

void
Foo::CIface(void *p)
{
	Foo *pThis = static_cast<Foo *>(p);

	pThis->i_++;
}

std::function<void(void)>
Foo::get_CXXIface()
{
	return [this] { work(); };
}

int main(int argc, char *argv[])
{
	Foo f;

//	test(Foo::CIface, &f);

	auto l = f.get_CXXIface();
	test(l);

	return 0;

}
