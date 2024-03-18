#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>

[[nodiscard]] inline bool are_equal_v1(double a, double b) noexcept
{
	return std::abs(a - b) < std::numeric_limits < double > ::epsilon();
}

[[nodiscard]] inline bool are_equal_v2(double a, double b, double epsilon) noexcept
{
	return std::abs(a - b) < epsilon;
}

[[nodiscard]] inline bool are_equal_v3(double a, double b, double relative_epsilon) noexcept
{
	return (std::abs(a - b) < (std::max(std::abs(a), std::abs(b)) * relative_epsilon));
}

[[nodiscard]] inline bool are_equal_v4(double a, double b, double epsilon, double relative_epsilon) noexcept
{
	if (std::abs(a - b) < epsilon) return true; else return are_equal_v3(a, b, relative_epsilon);
}

int main()
{
	std::cout << 1.67e-5 << std::endl; // note: scientific notation

	std::cout << std::fixed        << 3.14 << std::endl;
	std::cout << std::scientific   << 3.14 << std::endl;
	std::cout << std::defaultfloat << 3.14 << std::endl;

	const auto default_precision = std::cout.precision();

	constexpr auto max_precision = std::numeric_limits < double > ::digits10 + 1;

	for (auto p = 0; p <= max_precision; ++p) // good: formatted output
	{
		std::cout << std::setw(2) << std::right << std::setfill(' ') << p << ": " << 
			std::setprecision(p) << std::fixed << std::numbers::pi << std::endl;
	}

	std::cout << std::setprecision(default_precision);

	std::cout << std::numeric_limits < double > ::min() << std::endl; // note: 0.0
	std::cout << std::numeric_limits < double > ::max() << std::endl;

	if (std::numeric_limits < double > ::has_infinity)
	{
		std::cout << std::numeric_limits < double > ::infinity() << std::endl;
	}

	std::cout << std::log(-1) << std::endl; // note: NaN

	auto x = 0.0;
	auto y = 1.0;

	std::cout << -x / y << std::endl; // note: negative zero

	std::cout << std::boolalpha << are_equal_v1(1.0, 0.1 * 10) << std::endl;

	return 0;
}