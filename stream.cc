#include <iostream>
#include <sstream>

class logstream : public std::ostringstream
{
public:
	template <typename T>
	inline logstream & operator<<( const T & t )
	{
		(*(std::ostringstream*)this) << t;
		return *this;
	}
};

int main(int argc, char *argv[])
{
#if 0
	logstream l;

//	l << "test";
//

	std::stringstream ss;
	ss.fill('.');
	ss.width(8);

	ss << std::left << 42;
	ss <<  42;

	std::cout << ss.str();
#endif

	auto glambda = [](std::stringstream &ss, std::string name, auto val)
	{
		ss << "\t";
		ss.fill('.');
		ss.width(22);
		ss << std::left << name << " " << val << std::endl;
	};

	std::stringstream ss;

	glambda(ss, "foo", "bla");
	glambda(ss, "bar", 42);

	std::cout << ss.str();

	return 0;
}
