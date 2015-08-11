#include <iostream>

struct Foo1
{
};
using Foo = Foo1;

enum charEnum : char { A = 'A' };

void fct(char)      { std::cout << "fct(char)"      << std::endl; }
void fct(int)       { std::cout << "fct(int)"       << std::endl; }
void fct(long long) { std::cout << "fct(long long)" << std::endl; }

int main() 
{
	Foo foo;
    fct('A');
    fct(A);
}
