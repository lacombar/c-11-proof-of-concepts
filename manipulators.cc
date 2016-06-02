#include <iostream>
#include <iomanip>

#include "common.h"

// Private object constructed by the format object PutSquareBracket
struct SquareBracktAroundNextItem
{
	SquareBracktAroundNextItem(std::ostream& str)
		:m_str(str)
	{}
	std::ostream& m_str;
};

// New Format Object
struct PutSquareBracket
{};

// Format object passed to stream.
// All it does is return an object that can maintain state away from the
// stream object (so that it is not STICKY)
SquareBracktAroundNextItem operator<<(std::ostream& str,PutSquareBracket const& data)
{
	return SquareBracktAroundNextItem(str);
}

// The Non Sticky formatting.
// Here we temporariy set formating to fixed with a precision of 10.
// After the next value is printed we return the stream to the original state
// Then return the stream for normal processing.
template<typename T>
std::ostream& operator<<(SquareBracktAroundNextItem const& bracket,T const& data)
{
	bracket.m_str << '[' << data << ']';

	return bracket.m_str;
}


TEST(manipulators, main)
{
	std::stringstream ss;

	ss << PutSquareBracket() << 5.34;

	std::cout << ss.str() << std::endl;
}

