#include <iostream>
#include <memory>

#include "functor_.hh"

class Foo
{
public:
	static void CIface(void *);
	std::function<void(void)> get_CXXIface();
	void work();
private:
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

//	// C / CXX way
//	test({ &Foo::CIface, &f });

	// CXX way, through a generated object
//	auto l = f.get_CXXIface();

//	// CXX way, with direct lambda
//	test( [&f](){ f.work(); } );

//	// CXX way, using std::bind
//	test(std::bind(Foo::CIface, &f));

	return 0;

}
