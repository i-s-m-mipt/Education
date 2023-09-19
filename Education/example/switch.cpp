#include <iostream>

int main()
{
	auto x = 0;

	std::cin >> x;

	switch (x)
	{
	case 0:
	{
		std::cout << "case 0" << std::endl;
	}
	case 1:
	{
		std::cout << "case 1" << std::endl;
		break;
	}
	case 2:
	{
		std::cout << "case 2" << std::endl;
		break;
	}
	default:
	{
		std::cout << "default" << std::endl;
		break;
	}
	}

	return 0;
}