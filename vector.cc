#include <iostream>
#include <memory>

#include <gtest/gtest.h>

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
