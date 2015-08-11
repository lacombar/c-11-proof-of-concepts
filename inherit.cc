#include <iostream>

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


int main(int argc, char *argv[])
{
	Base *b = new Derived();

	std::cout << b << std::endl;
	std::cout << static_cast<Derived *>(b) << std::endl;
	std::cout << dynamic_cast<Derived *>(b) << std::endl;


	Base *b1 = new Base();
	std::cout << b1 << std::endl;
	std::cout << static_cast<Derived *>(b1) << std::endl;
	std::cout << dynamic_cast<Derived *>(b1) << std::endl;
	std::cout << reinterpret_cast<Derived *>(b1) << std::endl;


	return 0;
}
