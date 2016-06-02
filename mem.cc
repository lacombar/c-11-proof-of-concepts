#include <functional>
#include <iostream>

class Foo
{
public:
	enum Enum {
		bar,
		baz
	} val;

	Foo(Enum e) : e(e) {};

	operator int() const { return 1; };

	const Foo& operator=(const Enum e) {
		this->e = e;
		return *this;
	}
private:
	Enum e;
};

int main(int argc, char *argv[])
{
	[](){ Foo val = Foo::bar; int v = val; std::cout << v << std::endl;}();

	return 0;
}
