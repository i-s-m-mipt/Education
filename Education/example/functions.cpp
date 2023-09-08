#include <iostream>

[[nodiscard]] int f(int x);

[[nodiscard]] int g(int x, int y, int z = 1)
{
	return (x + y + z);
}

void h()
{
	auto x = 0;

	static auto y = 0;

	std::cout << x++ << ' ' << y++ << '\n';

	return;
}

void print(bool x)
{
	std::cout << x << '\n';
}

void print(double x)
{
	std::cout << x << '\n';
}

int factorial(int n)
{
	return (n < 2 ? 1 : n * factorial(n - 1));
}

inline auto max(int x, int y)
{
	return (x > y ? x : y);
}

int main()
{
	[[maybe_unused]] auto result = g(f(4), f(7));

	h(); 
	h(); 
	h();

	print(true);
	print(3.14);
//	print(1234); // error

	std::cout << factorial(5) << '\n';

	std::cout << max(4, 7) << '\n';

	return 0;
}

int f(int x)
{
	return (x + 1);
}