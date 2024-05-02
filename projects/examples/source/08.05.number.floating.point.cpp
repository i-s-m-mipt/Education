#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>

//  ================================================================================================

[[nodiscard]] inline constexpr bool are_equal_v1(double x, double y) noexcept
{
	return std::abs(x - y) < std::numeric_limits < double > ::epsilon();
}

[[nodiscard]] inline constexpr bool are_equal_v2(double x, double y, double epsilon) noexcept
{
	return std::abs(x - y) < epsilon;
}

[[nodiscard]] inline constexpr bool are_equal_v3(double x, double y, double relative_epsilon) noexcept
{
	return (std::abs(x - y) < (std::max(std::abs(x), std::abs(y)) * relative_epsilon));
}

[[nodiscard]] inline constexpr bool are_equal_v4(double x, double y, double epsilon, double relative_epsilon) noexcept
{
	if (std::abs(x - y) < epsilon) return true; else return are_equal_v3(x, y, relative_epsilon);
}

//  ================================================================================================

int main()
{
	std::cout << 1.67e-5 << std::endl; // note: scientific notation

	std::cout << std::fixed        << 3.14 << std::endl;
	std::cout << std::scientific   << 3.14 << std::endl;
	std::cout << std::defaultfloat << 3.14 << std::endl;

//  ================================================================================================

	const auto default_precision = std::cout.precision();

	constexpr auto max_precision = std::numeric_limits < double > ::digits10 + 1;

	for (auto p = 0; p <= max_precision; ++p) // good: formatted output
	{
		std::cout << std::setw(2) << std::right << std::setfill(' ') << p << ": " << 
			 std::setprecision(p) << std::fixed << std::numbers::pi  << std::endl;
	}

	std::cout << std::setprecision(default_precision);

//  ================================================================================================

	std::cout << std::numeric_limits < double > ::min() << std::endl; // note: 0.0
	std::cout << std::numeric_limits < double > ::max() << std::endl;

	if (std::numeric_limits < double > ::has_infinity)
	{
		std::cout << std::numeric_limits < double > ::infinity() << std::endl;
	}

//  ================================================================================================

	std::cout << errno << ' ' << std::log(-1) << ' ' << errno << std::endl; // note: C-style

	constexpr auto x = 0.0, y = 1.0;

	std::cout << -x / y << std::endl; // note: negative zero

//  ================================================================================================

	std::cout << std::boolalpha << are_equal_v1(1.0, 0.1 * 10) << std::endl;

	return 0;
}