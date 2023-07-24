#include <iostream>
#include <limits>

int main()
{
	std::cout << std::numeric_limits < int > ::min() << std::endl;
	std::cout << std::numeric_limits < int > ::max() << std::endl;

	system("pause");

	return 0;
}