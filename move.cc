#include "common.h"

struct A
{
    A() { std::cout << "default" << std::endl; }
    A(const A& a) = delete;
    A(A&& a) { std::cout << "move " << __func__ << std::endl; }
};

struct B
{
    B() { std::cout << "default" << std::endl; }
    B(const B& b) = delete;
    B(A a) : a(std::move(a)) { std::cout << "move " << __func__ << std::endl; }

private:
    A a;
};


TEST(move, bar)
{
	A a;
	B b(std::move(a));
}
