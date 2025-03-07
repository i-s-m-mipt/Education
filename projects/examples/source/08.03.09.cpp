#include <cassert>
#include <cmath>
#include <random>

//////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

//////////////////////////////////////////////////////////

int main()
{
    auto size = 100'000'000uz;

//  ------------------------------------------------------

	std::default_random_engine engine;

	std::uniform_real_distribution distribution(0.0, 1.0);

//  ------------------------------------------------------

	auto counter = 0uz;

//  ------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		auto x = distribution(engine);
		
		auto y = distribution(engine);

		if (x * x + y * y < 1)
		{
			++counter;
		}
	}

//  ------------------------------------------------------

	assert(equal(4.0 * counter / size, 3.141, 1e-3));
}