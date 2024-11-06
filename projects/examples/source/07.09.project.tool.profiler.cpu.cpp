#include <cassert>
#include <cmath>

//  ================================================================================================

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

//  ================================================================================================

int main()
{
	auto size = 1'000'000uz;
	
	auto result = 0.0;

	for (auto i = 0uz; i < size; ++i)
	{
		result += 
		(
			std::pow(std::sin(1.0 * i), 2.0) +
			std::pow(std::cos(1.0 * i), 2.0)
		);
	}

	assert(equal(result, static_cast < double > (size)));
}