#include <iostream>

#include <gtest/gtest.h>

struct B {};

struct X : B {
	operator B&() { return *this; };
	operator const B*() const { return nullptr; };
};
 
int main()
{
	X x;
	B& b1 = x;                  // does not call X::operatorB&()
	B& b2 = static_cast<B&>(x); // does not call X::operatorB&
	B& b3 = x.operator B&();    // calls X::operator&

	std::cout << &x << std::endl;


	const X x1;

	const B* b4 = x1.operator const B*();

	std::cout << b4 << std::endl;
}
