#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <vector>

enum
{
	f_addition,
	f_subtraction,
	f_multiplication,
	f_division,

	size,
};

void print(int x)
{
	std::cout << x << std::endl;
}

void apply(void (*f)(int), int argument)
{
	f(argument);
}

int main()
{
	void (*print_ptr)(int) = &print;

	(*print_ptr)(42);

	apply(print, 42);

	auto lambda_1 = []() {};

	auto a = 0;
	auto b = 1;

	auto lambda_2 = [&a, b](auto c)
		{
			a = b + c;
		};

	lambda_2(2);

	std::cout << a << std::endl;

	auto lambda_3 = [b](auto c) mutable
		{
			b += c;
		};

	std::cout << b << std::endl;

	std::array < std::function < int(int, int) >, size > functions;

	functions[f_addition] = [](auto x, auto y) { return x + y; };
	functions[f_subtraction] = [](auto x, auto y) { return x - y; };
	functions[f_multiplication] = [](auto x, auto y) { return x * y; };
	functions[f_division] = [](auto x, auto y) { return x / y; };

	auto x = 8;
	auto y = 4;

	std::cout << functions.at(f_subtraction)(x, y) << std::endl;

	std::vector < int > v({ 2, 5, 4, 1, 3 });

	std::for_each(std::begin(v), std::end(v), [b](auto& x) { x += b; });
	std::for_each(std::begin(v), std::end(v), [](auto x) { std::cout << x << std::endl; });

	return 0;
}