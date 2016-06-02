#include <iostream>
#include <string>
#include <thread>
#include <mutex>

#include <memory>

#include "common.h"

thread_local unsigned int rage = 1; 
std::mutex cout_mutex;


struct A
{
	A() { std::cout << __func__ << std::endl; };
	~A() { std::cout << __func__ << std::endl; }

	thread_local static std::shared_ptr<int> p;
};

thread_local std::shared_ptr<int> A::p = nullptr;

void increase_rage(const std::string& thread_name)
{
	A a;

	a.p = std::make_shared<int>(1); // modifying outside a lock is okay; this is a thread-local variable
	std::lock_guard<std::mutex> lock(cout_mutex);
	std::cout << "Rage counter for " << thread_name << ": " << a.p << '\n';
}

TEST(foo, bar)
{
	A a;

	std::thread t0(increase_rage, "t0"), t1(increase_rage, "t1");

	{
		std::lock_guard<std::mutex> lock(cout_mutex);
		std::cout << "Rage counter for main: " << rage << '\n';
	}

	t0.join();
	t1.join();
}
