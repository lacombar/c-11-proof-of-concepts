#include "common.h"

TEST(chrono, to_usec)
{
	auto epoch = std::chrono::system_clock::now().time_since_epoch();

	auto nano = std::chrono::duration_cast<std::chrono::nanoseconds>(epoch).count();
	auto micro = std::chrono::duration_cast<std::chrono::microseconds>(epoch).count();
	auto milli = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();

	auto _double = std::chrono::duration_cast<double>(now.)
	
	std::cout << nano << std::endl;
	std::cout << micro << std::endl;
	std::cout << milli << std::endl;
}
