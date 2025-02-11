#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

///////////////////////////////////////////////////////////////////////////////////

auto test(std::size_t size)
{
	auto x = 0.0;

	for (auto i = 0uz; i < size; ++i)
	{
		x += std::pow(std::sin(i), 2.0) + std::pow(std::cos(i), 2.0);
	}

	return x;
}

///////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

///////////////////////////////////////////////////////////////////////////////////

// support: valgrind --tool=callgrind ./07.08.support.profiler.valgrind

// support: valgrind --leak-check=yes ./07.08.support.profiler.valgrind

int main() 
{
	{
		assert(equal(test(1'000), 1'000.0));
	}

//  -------------------------------------------------------------------------------

	{
		auto array = new int[5]{ 1, 2, 3, 4, 5 };

		array[1'000] = 1;

//  	delete[] array; // bad

		std::cout << "main : enter char to continue : "; char x = 0; std::cin >> x;
	}
}