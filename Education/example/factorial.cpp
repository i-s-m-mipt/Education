#include <iostream>

int f(int x)
{
	auto result = 1;

	for (int i = 2; i <= x; ++i)
	{
		result *= i;
	}

	return result;
}

int main()
{
	std::cout << f(0)  << std::endl;
	std::cout << f(1)  << std::endl;
	std::cout << f(5)  << std::endl;
	std::cout << f(20) << std::endl;

	system("pause");

	return 0;
}