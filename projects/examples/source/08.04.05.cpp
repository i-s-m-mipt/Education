/////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>

/////////////////////////////////////////////////////////////////

#include <boost/timer/timer.hpp>

/////////////////////////////////////////////////////////////////

auto calculate(std::size_t size)
{
	auto x = 0.0;

	for (auto i = 0uz; i < size; ++i)
	{
		x += std::pow(std::sin(i), 2) + std::pow(std::cos(i), 2);
	}

	return x;
}

/////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

/////////////////////////////////////////////////////////////////

int main()
{
    boost::timer::cpu_timer timer;

//  ------------------------------------------------

    assert(equal(calculate(1'000'000), 1'000'000));

//  ------------------------------------------------

    std::cout << "main : timer :" << timer.format();
}

/////////////////////////////////////////////////////////////////