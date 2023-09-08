#include <iostream>

int main()
{
	int x{};
	int y{};

	std::cout << "Enter two numbers separated by a space symbol: ";

	std::cin >> x >> y;

	std::cout << "You entered " << x << " and " << y << '\n';

	return 0;
}
