/////////////////////////////////////////////////////////////////////////

// chapter : Debugging and Profiling Tools

/////////////////////////////////////////////////////////////////////////

// content : Profiling
//
// content : Profile-Guided Optimization (PGO)
//
// content : Algorithm std::ranges::iota
//
// content : Functions std::pow, std::sin and std::cos
//
// content : Options -fprofile-generate and -fprofile-use
//
// content : Tool time

/////////////////////////////////////////////////////////////////////////

// support : time ./07.17.01
//
// support : time ./07.17.02

/////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <numeric>
#include <vector>

/////////////////////////////////////////////////////////////////////////

auto calculate(std::vector < int > const & vector, int threshold)
{
	auto x = 0.0;

    for (auto i = 0uz; i < 1 << 10; ++i)
	{
        for (auto element : vector)
		{
            if (element > threshold)
			{
                x += std::pow(std::sin(x), 2) + std::pow(std::cos(x), 2);
            }
			else
			{
                ++x;
            }
        }
    }

    return x;
}

/////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

/////////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector(1 << 20, 0);

//  -----------------------------------------------------------------

    std::ranges::iota(vector, 1);

//  -----------------------------------------------------------------

	assert(equal(calculate(vector, (1 << 20) - (1 << 10)), 1 << 30));
}

/////////////////////////////////////////////////////////////////////////