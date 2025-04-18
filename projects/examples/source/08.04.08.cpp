////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <numbers>
#include <string>

////////////////////////////////////////////////////////////////

using namespace std::literals;

////////////////////////////////////////////////////////////////

struct Entity 
{ 
	unsigned long long x = 0;
};

////////////////////////////////////////////////////////////////

auto operator""_E(unsigned long long x)
{
	return Entity(x);
}

////////////////////////////////////////////////////////////////

auto operator""_deg_to_rad(long double x)
{
	return x * std::numbers::pi_v < long double > / 180;
}

////////////////////////////////////////////////////////////////

auto pow(int x, int y) -> int
{
	return y > 0 ? x * pow(x, y - 1) : 1;
}

////////////////////////////////////////////////////////////////

template < char D, char ... Ds > auto handler() -> int
{
	auto x = D - '0';

//  ------------------------------------------------------------
	
	if constexpr (sizeof...(Ds) > 0)
	{
		return x * pow(3, sizeof...(Ds)) + handler < Ds... > ();
	}
	else
	{
		return x;
	}
}
	
////////////////////////////////////////////////////////////////

template < char ... Ds > auto operator""_b3()
{
	return handler < Ds... > ();
}

////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

////////////////////////////////////////////////////////////////

int main()
{
	auto string = "aaaaa"s;

//  -----------------------------------------------------

	[[maybe_unused]] auto entity = 1_E;

//  -----------------------------------------------------

	assert(equal(90.0_deg_to_rad, std::numbers::pi / 2));

//  -----------------------------------------------------

	assert(210_b3 == 21);
}

////////////////////////////////////////////////////////////////