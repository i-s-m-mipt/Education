#include <iostream>

int main()
{
	auto x = true;
	auto y = false;

	auto result = (x || y) && !y;

	if (x || y)
	{
		std::cout << std::boolalpha << result << std::endl;
	}

	std::cout << sizeof(x) << std::endl;

	system("pause");

	return 0;
}