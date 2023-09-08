#include <iostream>

int factorial(int n)
{
	return (n < 2 ? 1 : n * factorial(n - 1));
}

void print(int x)
{
	std::cout << x << '\n';

	return;
}

[[nodiscard]] int f(int x);

int max(int x, int y)
{
	return (x > y ? x : y);
}

void g(int x)
{
	int y = 42;
}

int main()
{
	std::cout << factorial(5) << '\n';

	print(42);

	f(1); // warning

	std::cout << max(13, 19) << '\n';

	std::cout << max(2 + 5, 3 + 6) << '\n';

	return 0;
}

int f(int x)
{
	return x + 42;
}