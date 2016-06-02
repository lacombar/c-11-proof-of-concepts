#include "common.h"

#include <tuple>

using type = std::tuple<std::string, std::string>;

std::vector<type> types {
	{ std::make_tuple( "", "" ) }
};

