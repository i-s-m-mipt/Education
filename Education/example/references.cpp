#include <iostream>

int main()
{
	auto x = 0;

	auto & rx = x;

	rx = 42;

	const auto & rcx = x;
	const auto & rcv = 42;

	return 0;
}