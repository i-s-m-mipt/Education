/////////////////////////////////////////////////

// chapter : Parallel Programming

/////////////////////////////////////////////////

// content : Detaching Threads
//
// content : Daemon Threads
//
// content : Function std::this_thread::sleep_for

/////////////////////////////////////////////////

#include <cassert>
#include <chrono>
#include <print>
#include <thread>

/////////////////////////////////////////////////

using namespace std::literals;

/////////////////////////////////////////////////

void test_v1()
{
    std::print("test\n");
}

/////////////////////////////////////////////////

void test_v2(int * x)
{
	std::this_thread::sleep_for(1s);

    ++(*x);
}

/////////////////////////////////////////////////

void test_v3()
{
    auto x = 1;

    std::thread thread(test_v2, &x);

//	thread.detach(); // error

    thread.join();
}

/////////////////////////////////////////////////

int main()
{
    std::thread thread(test_v1);

//  --------------------------------

    thread.detach();

//  --------------------------------

    test_v3();

//  --------------------------------

    std::this_thread::sleep_for(5s);
}

/////////////////////////////////////////////////