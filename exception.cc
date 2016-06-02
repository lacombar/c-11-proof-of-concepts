#include <iostream>

#include <gtest/gtest.h>

#define TRACE()		std::cout << __func__ << std::endl

void a()
{
	throw std::string("foo");
}

void b()
{

	std::cout << "terminate" << std::endl;
}

int main()
{

	std::set_terminate(b);

	a();
	return 0;
}



