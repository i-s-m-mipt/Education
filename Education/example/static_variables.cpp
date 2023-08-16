#include <iostream>

void f()
{
	auto x = 0;

	static auto y = 0;

	std::cout << x++ << std::endl;
	std::cout << y++ << std::endl;
}

int main()
{
	f();
	f();
	f();

	return 0;
}