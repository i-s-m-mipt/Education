#include <chrono>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <thread>

using namespace std::literals;

//  ================================================================================================

void f(std::size_t size)
{
	const auto array = new int[size]{};

	std::iota(array, array + size, 1);

	std::this_thread::sleep_for(1s);

//  delete[] array; // bad
}

//  ================================================================================================

int main()
{
	f(1'000'000);
	f(1'000'000);
	f(1'000'000);
	f(1'000'000);
	f(1'000'000);

	return 0;
}