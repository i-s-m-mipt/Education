#include <iostream>

int main()
{
	auto x = true;
	auto y = false;

	auto result = (x || y) && !y;

	if (x || y)
	{
		std::cout << std::boolalpha   << x << ' ' << y << std::endl;
		std::cout << std::noboolalpha << x << ' ' << y << std::endl;
	}

	std::cout << sizeof(x) << std::endl;

	return 0;
}