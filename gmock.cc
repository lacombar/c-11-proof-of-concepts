#include <memory>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#if 0
class moveable_noncopyable
{
public:
	moveable_noncopyable() { }

	moveable_noncopyable(const moveable_noncopyable&) = delete;
	moveable_noncopyable& operator= (const moveable_noncopyable&) = delete;

	moveable_noncopyable(moveable_noncopyable&&) = default;
	moveable_noncopyable& operator= (moveable_noncopyable&&) = default;
};

class C0 : public moveable_noncopyable
{
public:
	C0(int i) : i_(i)
	{
	};
	int i_;
};

class IC1
{
	virtual void f(C0 c0) = 0;
};

class MockC1 : public IC1
{
public:
	MOCK_METHOD1(f, void(C0 c0));
};

void g(C0 c0)
{
	std::cout << c0.i_ << std::endl;
}

TEST(gmock, invoke_move_only)
{
	MockC1 mockC1;
	C0 c0(42);

	using ::testing::_;
	using ::testing::Invoke;

	EXPECT_CALL(mockC1, f(_)).WillOnce(Invoke(g));

	mockC1.f(std::move(c0));
}

#endif

using namespace ::testing;

struct MockA
{
	MOCK_METHOD0(MakeUnique, std::unique_ptr<int>());
};

TEST(gmock, return_move_only)
{
	MockA* mock = new MockA();

	std::unique_ptr<int> i(new int(19));

	EXPECT_CALL(*mock, MakeUnique()).WillOnce(Return(ByMove(std::move(i))));

	mock->MakeUnique();
}

