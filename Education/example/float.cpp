#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>

auto are_equal(double lhs, double rhs)
{
	return (std::abs(lhs - rhs) <= std::numeric_limits < double > ::epsilon());
}

int main()
{
	std::cout << 3.14    << std::endl;
	std::cout << 4e2     << std::endl;
	std::cout << 1.67e-5 << std::endl;

	auto f = 3.14f;

	std::cout << std::fixed        << 12.34 << std::endl;
	std::cout << std::scientific   << 12.34 << std::endl;
	std::cout << std::defaultfloat << 12.34 << std::endl;

	const auto pi = std::numbers::pi_v < long double >;

	const auto default_precision = std::cout.precision();

	const auto max_precision = std::numeric_limits < long double > ::digits10 + 1;

	std::cout << default_precision << ' ' << max_precision << std::endl;

	for (auto p = 0; p <= max_precision; ++p)
	{
		std::cout << std::setw(2) << p << " - " << std::setprecision(p) << std::fixed << pi << '\n';
	}

	std::cout << std::setprecision(default_precision);

	std::cout << std::numeric_limits < int > ::min() << std::endl;
	std::cout << std::numeric_limits < int > ::max() << std::endl;

	std::cout << std::boolalpha << std::numeric_limits < double > ::has_infinity << std::endl;

	auto max = std::numeric_limits < double > ::max();
	auto inf = std::numeric_limits < double > ::infinity();

	if (inf > max)
	{
		std::cout << std::defaultfloat << inf << ' ' << max << std::endl;
	}

	std::cout << std::log(-1) << std::endl;

	auto x = 0.0;
	auto y = 1.0;

	std::cout << -x / y << std::endl;

	std::cout << std::boolalpha << are_equal(1.0, 0.1 * 10) << std::endl;

	system("pause");

	return 0;
}