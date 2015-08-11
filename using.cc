#include <iostream>

struct Foo
{
	int a;
};

class Foo
{
	public:
	Foo()
	{
		std::cout << __func__ << std::endl;
	}
};

using foo = Foo;

int main(int argc, char *argv[])
{
	foo f;

	return 0;
}
