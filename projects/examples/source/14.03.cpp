//////////////////////////////////////

#include <cassert>
#include <chrono>
#include <print>
#include <thread>

//////////////////////////////////////

using namespace std::literals;

//////////////////////////////////////

void test_v1()
{
    std::print("test\n");
}

//////////////////////////////////////

void test_v2(int * x)
{
	std::this_thread::sleep_for(5s);
        
    ++(*x);
}

//////////////////////////////////////

int main()
{
    std::thread thread_1(test_v1);

//  ----------------------------------

    thread_1.detach();

//  ----------------------------------

    auto x = 1;

//  ----------------------------------
	
	std::thread thread_2(test_v2, &x);

//  ----------------------------------

	thread_2.join();

//  ----------------------------------

//	thread_2.detach(); // error
}

//////////////////////////////////////