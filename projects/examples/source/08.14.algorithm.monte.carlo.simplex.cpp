#include <cassert>
#include <cmath>
#include <numbers>
#include <random>

//  ================================================================================================

struct Vector 
{ 
	double x = 0.0;
	double y = 0.0;
	double z = 0.0; 
};

//  ================================================================================================

auto operator*(const Vector & a, const Vector & b)
{
	return Vector
	( 
		a.y * b.z - a.z * b.y,
	   -a.x * b.z + a.z * b.x,
		a.x * b.y - a.y * b.x 
	);
}

//  ================================================================================================

auto evaluate(std::size_t size)
{
	std::default_random_engine engine;

	std::uniform_real_distribution < double > distribution(0.0, 2.0 * std::numbers::pi);

	Vector PA(0.0, -1.0);

	auto counter = 0uz;

	for (auto i = 0uz; i < size; ++i)
	{
		auto w_B = distribution(engine);
		auto w_C = distribution(engine);

		Vector PB(std::cos(w_B), std::sin(w_B), 0.0);
		Vector PC(std::cos(w_C), std::sin(w_C), 0.0);

		auto a = (PA * PB).z;
		auto b = (PB * PC).z;
		auto c = (PC * PA).z;

		if 
		(
			(a >= 0.0 && b >= 0.0 && c >= 0.0) ||
			(a <= 0.0 && b <= 0.0 && c <= 0.0)
		)
		{
			++counter;
		}
	}

	return 1.0 * counter / size;
}

//  ================================================================================================

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

//  ================================================================================================

int main()
{
	assert(equal(evaluate(100'000'000), 0.250, 1e-3));
}