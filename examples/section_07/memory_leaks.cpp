#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

using namespace std::literals;

void f(std::size_t size)
{
	auto a = new int[size]{}; // note: dynamic allocation

	for (std::size_t i = 0; i < size; ++i)
	{
		a[i] = static_cast < int > (i + 1);
	}

	std::this_thread::sleep_for(1s); // note: delay

//  delete[] a; // bad: memory leak if skipped
}

int main()
{
	f(5'000'000);
	f(5'000'000);
	f(5'000'000);
	f(5'000'000);
	f(5'000'000);

	return 0;
}