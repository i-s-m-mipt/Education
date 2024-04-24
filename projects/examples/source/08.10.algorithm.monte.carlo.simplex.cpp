#include <cmath>
#include <iostream>
#include <numbers>
#include <random>

// =================================================================================================

struct Vector { double x{}, y{}, z{}; };

[[nodiscard]] inline constexpr Vector operator*(Vector a, Vector b) noexcept
{
	return { a.y * b.z - a.z * b.y,
	   		-a.x * b.z + a.z * b.x,
			 a.x * b.y - a.y * b.x }; // note: only z needed from result
}

// =================================================================================================

[[nodiscard]] double calculate_probability(std::size_t size) noexcept
{
	std::mt19937_64 engine(std::random_device{}());

	std::uniform_real_distribution < double > distribution(0.0, 2.0 * std::numbers::pi);

	constexpr Vector PA {0.0, -1.0}; // note: P states for circle center in { 1.0, 1.0 }

	std::size_t counter = 0;

	for (std::size_t i = 0; i < size; ++i)
	{
		const auto w_B = distribution(engine);
		const auto w_C = distribution(engine);

		const auto x_b = std::cos(w_B); // note: r = 1.0
		const auto y_b = std::sin(w_B);
		const auto x_c = std::cos(w_C);
		const auto y_c = std::sin(w_C);

		const Vector PB {x_b, y_b};
		const Vector PC {x_c, y_c};

		const auto a = (PA * PB).z; // note: barycentric coordinate method
		const auto b = (PB * PC).z;
		const auto c = (PC * PA).z;

		if ((a >= 0.0 && b >= 0.0 && c >= 0.0) ||
			(a <= 0.0 && b <= 0.0 && c <= 0.0))
		{
			++counter;
		}
	}

	return 1.0 * counter / size;
}

// =================================================================================================

int main()
{
	std::cout << calculate_probability(10'000'000) << std::endl; // note: ~0.25

	return 0;
}