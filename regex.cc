#include "common.h"

TEST(regex, foo)
{
	std::vector<std::pair<std::regex, std::function<void(const std::string&)>>> entries
	{
		{ std::regex("\\[a\\].*"), [](const std::string&){ std::cout << 1 << std::endl; } },
	};

	std::vector<std::string> strings { "[a]", "[b]", "[cc]" };

	for (auto& string : strings)
	{
		for (auto& entry : entries )
		{
			std::smatch base_match;

			if (std::regex_match(string, base_match, entry.first))
			{
				entry.second(string);
				return;
			}
		}
	}
}
