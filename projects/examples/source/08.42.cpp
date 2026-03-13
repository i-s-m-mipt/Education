////////////////////////////////////////////////////////////////////////////////

// chapter : Number Processing

////////////////////////////////////////////////////////////////////////////////

// section : Chrono Management

////////////////////////////////////////////////////////////////////////////////

// content : Literal Operators
//
// content : Operators ""s
//
// content : Namespace std::literals
//
// content : User-Defined Literal Operators

////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <chrono>
#include <cmath>
#include <numbers>
#include <string>
#include <type_traits>

////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

////////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	unsigned long long int x = 0;
};

////////////////////////////////////////////////////////////////////////////////

auto operator""_E(unsigned long long int x)
{
	return Entity(x);
}

////////////////////////////////////////////////////////////////////////////////

auto operator""_deg_to_rad(long double x)
{
	return x * std::numbers::pi_v < long double > / 180;
}

////////////////////////////////////////////////////////////////////////////////

auto pow(int x, int y) -> int
{
	return y > 0 ? x * pow(x, y - 1) : 1;
}

////////////////////////////////////////////////////////////////////////////////

template < char D, char ... Ds > auto make_integer() -> int
{
	auto x = D - '0';
	
	if constexpr (sizeof...(Ds) > 0)
	{
		return x * pow(3, sizeof...(Ds)) + make_integer < Ds... > ();
	}
	else
	{
		return x;
	}
}
	
////////////////////////////////////////////////////////////////////////////////

template < char ... Ds > auto operator""_b3()
{
	return make_integer < Ds... > ();
}

////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto string = "aaaaa"s;

//  ----------------------------------------------------------------------------

	static_assert(std::is_same_v < decltype(string), std::string > );

//  ----------------------------------------------------------------------------

	auto duration = 1s;

//  ----------------------------------------------------------------------------

	static_assert(std::is_same_v < decltype(duration), std::chrono::seconds > );

//  ----------------------------------------------------------------------------

	auto entity = 1_E;

//  ----------------------------------------------------------------------------

	static_assert(std::is_same_v < decltype(entity), Entity > );

//  ----------------------------------------------------------------------------

	assert(equal(90.0_deg_to_rad, std::numbers::pi / 2));

//  ----------------------------------------------------------------------------

	assert(210_b3 == 21);
}

////////////////////////////////////////////////////////////////////////////////