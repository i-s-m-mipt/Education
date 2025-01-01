#include <cassert>
#include <cmath>

//  ================================================================================================

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

//  ================================================================================================

int main() // support: valgrind --tool=callgrind ./07.09.project.tool.profiler.cpu
{	
	auto result = 0.0;

	for (auto i = 0uz; i < 1'000; ++i)
	{
		result += 
		(
			std::pow(std::sin(1.0 * i), 2.0) +
			std::pow(std::cos(1.0 * i), 2.0)
		);
	}

	assert(equal(result, 1'000.0));
}