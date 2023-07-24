#include <cmath>
#include <iostream>
#include <limits>

auto are_equal(double lhs, double rhs)
{
	return (std::abs(lhs - rhs) <= std::numeric_limits < double > ::epsilon());
}

int main()
{
	std::cout << std::boolalpha << are_equal(1.0, 0.1 * 10) << std::endl;

	system("pause");

	return 0;
}