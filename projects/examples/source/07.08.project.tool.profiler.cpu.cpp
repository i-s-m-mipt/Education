#include <cassert>
#include <cmath>

//////////////////////////////////////////////////////////////////////////////////

auto test(std::size_t size)
{
	auto x = 0.0;

	for (auto i = 0uz; i < size; ++i)
	{
		x += std::pow(std::sin(i), 2.0) + std::pow(std::cos(i), 2.0);
	}

	return x;
}

//////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

//////////////////////////////////////////////////////////////////////////////////

int main() // support: valgrind --tool=callgrind ./07.09.project.tool.profiler.cpu
{
	assert(equal(test(1'000), 1'000.0));
}