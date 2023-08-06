#include <iostream>

int main()
{
	int a[10]{};

	*a = 42;

	*(a + 5) = 42;

	std::cout << a[5]         << std::endl;
	std::cout << *(&a[0] + 5) << std::endl;
	std::cout << *(a + 5)     << std::endl;
	std::cout << *(5 + a)     << std::endl;
	std::cout << 5[a]         << std::endl;

	auto b = a + 5;
	auto c = a + 7;

	auto delta = c - b;

	std::cout << delta << std::endl;

	char string[] = "Hello";

	for (char * p = string; *p != 0; ++p)
	{
		std::cout << *p;
	}

	return 0;
}