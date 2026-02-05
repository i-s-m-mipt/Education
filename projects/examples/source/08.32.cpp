///////////////////////////////////////////////////////////////////////////

// chapter : Number Processing

///////////////////////////////////////////////////////////////////////////

// section : Random Numbers

///////////////////////////////////////////////////////////////////////////

// content : W.L.Putnam Mathematical Competition Proble
//
// content : Vector Product
//
// content : Operator *
//
// content : Barycentric Coordinate Method

///////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <numbers>
#include <random>

///////////////////////////////////////////////////////////////////////////

struct Vector 
{ 
	double x = 0, y = 0, z = 0;
};

///////////////////////////////////////////////////////////////////////////

auto operator*(Vector const & a, Vector const & b)
{
	return Vector
	( 
		a.y * b.z - a.z * b.y,

	   -a.x * b.z + a.z * b.x,

		a.x * b.y - a.y * b.x 
	);
}

///////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

///////////////////////////////////////////////////////////////////////////

int main()
{
	auto size = 100'000'000uz;

//  -----------------------------------------------------------------------

	std::uniform_real_distribution distribution(0.0, 2 * std::numbers::pi);

//  -----------------------------------------------------------------------

	std::default_random_engine engine;

//  -----------------------------------------------------------------------

	Vector PA(0, -1, 0);

//  -----------------------------------------------------------------------

	auto counter = 0uz;

//  -----------------------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		auto w_B = distribution(engine);
		
		auto w_C = distribution(engine);

	//  -----------------------------------------------------

		Vector PB(std::cos(w_B), std::sin(w_B), 0);

		Vector PC(std::cos(w_C), std::sin(w_C), 0);

	//  -----------------------------------------------------

		auto alpha_1 = (PA * PB).z;
		
		auto alpha_2 = (PB * PC).z;
		
		auto alpha_3 = (PC * PA).z;

	//  -----------------------------------------------------

		counter +=
		(
			(alpha_1 >= 0 && alpha_2 >= 0 && alpha_3 >= 0) ||
			
			(alpha_1 <= 0 && alpha_2 <= 0 && alpha_3 <= 0)
		);
	}

//  -----------------------------------------------------------------------

	assert(equal(1.0 * counter / size, 0.250, 1e-3));
}

///////////////////////////////////////////////////////////////////////////