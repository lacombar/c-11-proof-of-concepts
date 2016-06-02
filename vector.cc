#include "common.h"

template <typename T>
std::vector<T> operator+(const std::vector<T> &A, const std::vector<T> &B)
{
    std::vector<T> AB;
    AB.reserve( A.size() + B.size() );                // preallocate memory
    AB.insert( AB.end(), A.begin(), A.end() );        // add A;
    AB.insert( AB.end(), B.begin(), B.end() );        // add B;
    return AB;
}

template <typename T>
std::vector<T> &operator+=(std::vector<T> &A, const std::vector<T> &B)
{
    A.reserve( A.size() + B.size() );                // preallocate memory without erase original data
    A.insert( A.end(), B.begin(), B.end() );         // add B;
    return A;                                        // here A could be named AB
}

TEST(vector, trimming)
{
	std::vector<char> A(10, 'A');
	std::vector<char> B(10, 'B');

	std::vector<char> C(20);

	C = A + B;

	C.erase(C.begin(), C.begin()+10);

	for (auto c : C)
		std::cout << c;

	std::cout << std::endl;
}

struct B
{
	B() = delete;
};

TEST(vector, no_default_constructor)
{
	std::vector<B> b;

	//b.resize(8);
}

TEST(vector, constructor)
{
	std::vector<int> v(10, 100);

	std::cout << v.size() << " " << v[9] <<std::endl;
}

TEST(vector, reserve)
{
	std::vector<int> v;

	v.reserve(42);

	std::cout << v.size() << std::endl;

	v[10] = 1;

	std::cout << v.size() << std::endl;
}


TEST(vector, from_c_array)
{
	int a[] = { 0, 1, 2, 3, 4};

	std::vector<int> good{ 0, 1, 2, 3, 4 };

	std::vector<int> test(&a[0], &a[0] + 5);

	EXPECT_EQ(test, good);
}

