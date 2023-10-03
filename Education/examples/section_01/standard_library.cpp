#include <cmath>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>

int main()
{
//	using namespace std; // bad: dangerous in big projects
	
	int x{};
	int y{};

	std::cout << "Enter two numbers separated by a space symbol: ";

	std::cin >> x >> y;

	std::cout << "You entered " << x << " and " << y << std::endl;

	std::string prompt = "Hello";

	std::string name{};

	std::cout << "Enter your name in english: ";

	std::cin >> name;

	std::cout << prompt << ", " << name << std::endl;

	std::cout << std::abs(-1.0)     << std::endl;
	std::cout << std::sin(2.0)      << std::endl;
	std::cout << std::sqrt(4.0)     << std::endl;
	std::cout << std::pow(2.0, 3.0) << std::endl;
	std::cout << std::gcd(128, 360) << std::endl;
	std::cout << std::lcm(14, 21)   << std::endl;

	std::swap(x, y);

	std::cout << "Now x = " << x << " and y = " << y << std::endl;

	return 0;
}