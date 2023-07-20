#include <iostream>

int main()
{
	auto x = true;
	auto y = false;

	auto z = (x || y) && !y;

	if (x)
	{
		std::cout << std::boolalpha << z << std::endl;
	}

	system("pause");

	return 0;
}