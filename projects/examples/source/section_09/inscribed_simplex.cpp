#include <cmath>
#include <iostream>
#include <numbers>
#include <random>

struct Vector
{
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;

}; // struct Vector

[[nodiscard]] inline Vector vector_product(Vector a, Vector b) noexcept
{
	return { 
        a.y * b.z - a.z * b.y, 
       -a.x * b.z + a.z * b.x, 
        a.x * b.y - a.y * b.x }; // note: only z needed from result
}

[[nodiscard]] double calculate_probability(std::size_t size)
{
	std::mt19937 engine(std::random_device{}());

	std::uniform_real_distribution < double > distribution(0.0, 2.0 * std::numbers::pi);

    Vector PA = { 0.0, -1.0 }; // note: P states for circle center in { 1.0, 1.0 }

    std::size_t counter = 0;

	for (std::size_t i = 0; i < size; ++i)
	{
		auto w_B = distribution(engine);
        auto w_C = distribution(engine);
		
		auto x_b = std::cos(w_B); // note: r = 1.0
		auto y_b = std::sin(w_B);
        auto x_c = std::cos(w_C);
		auto y_c = std::sin(w_C);

        Vector PB = { x_b, y_b };
		Vector PC = { x_c, y_c };

		auto a = vector_product(PA, PB).z; // note: barycentric coordinate method
		auto b = vector_product(PB, PC).z;
		auto c = vector_product(PC, PA).z;

		if ((a >= 0.0 && b >= 0.0 && c >= 0.0) || 
            (a <= 0.0 && b <= 0.0 && c <= 0.0))
		{
			++counter;
		}
	}

	return 1.0 * counter / size;
}

int main()
{
	std::cout << calculate_probability(10'000'000) << std::endl; // note: ~0.25

	return 0;
}