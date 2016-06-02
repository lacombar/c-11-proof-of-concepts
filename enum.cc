#include "common.h"

struct A
{
	enum class EnumA
	{
		eNone
	};

	A(A::EnumA e) { }
};

TEST(enum, enum_class)
{
	A a(A::EnumA::eNone);
}

