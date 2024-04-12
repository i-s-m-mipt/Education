#include <chrono>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <thread>

using namespace std::literals;

void f(std::size_t size)
{
	const auto array = new int[size]{}; // note: dynamic allocation

	std::iota(array, array + size, 1); // note: generate range 1, 2, 3, ...

	std::this_thread::sleep_for(1s); // note: delay

//  delete[] array; // bad: memory leak if skipped
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