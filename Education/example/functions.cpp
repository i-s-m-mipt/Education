#include <iostream>

[[nodiscard]] int f(int x); // note: forward declaration

[[nodiscard]] int g(int x, int y, int z = 1)
{
	return (x + y + z);
}

void test_pointers(int * x, const int * y)
{
	if (!x || !y)
	{
		return;
	}

	std::cout << *x << ' ' << *y << '\n';

	++(*x);
//	++(*y); // error: pointer to constant value

	std::cout << *x << ' ' << *y << '\n';
}

void test_references(int & x, const int & y)
{
	std::cout << x << ' ' << y << '\n';

	++x;
//	++y; // error: constant reference

	std::cout << x << ' ' << y << '\n';
}

[[maybe_unused]] void set_code(int * code = nullptr) // good: nullptr as default argument
{
	[[maybe_unused]] auto local_code = (code ? *code : 1234);
}

void test_array(int * a, int size) // note: array size as additional argument
{
	for (auto i = 0; i < size; ++i)
	{
		std::cout << a[i];

		std::cout << (i + 1 == size ? '\n' : ' ');
	}
}

/*
int * get_dangling_pointer()
{
	int d = 42; // good: static const int d = 42;

	return &d; // warning: dangling pointer to non-static local variable
}
*/

/*
int & get_dangling_reference()
{
	int d = 42; // good: static const int d = 42;

	return d; // warning: dangling reference to non-static local variable
}
*/

void h()
{
	auto x = 0;

	static auto y = 0; // note: once initialized static variable

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
	return (n < 2 ? 1 : n * factorial(n - 1)); // good: compact recursion
}

inline auto max(int x, int y) // good: return type deduction in small function
{
	return (x > y ? x : y);
}

int main()
{
//	f(42); // warning: nodiscard function

	[[maybe_unused]] auto s = g(f(4), f(7)); // note: unspecified arguments evaluation order

	auto x = 0;
	auto y = 0;

	test_pointers(&x, &y);

	std::cout << x << ' ' << y << '\n';

	test_references(x, y);

	std::cout << x << ' ' << y << '\n';

	const auto size = 5;

	int array_1[size]{ 1, 2, 3, 4, 5 };

	test_array(array_1, size); // note: uniform syntax

	auto array_2 = new int[size]{ 1, 2, 3, 4, 5 };

	test_array(array_2, size);

	delete[] array_2;

//	std::cout << *get_dangling_pointer() << '\n'; // bad: undefined behavior

//	std::cout << get_dangling_reference() << '\n'; // bad: undefined behavior

	h();
	h();
	h();

	print(true);
	print(3.14);
//	print(1234); // error: ambiguous function overloading

	std::cout << factorial(5) << '\n';

	std::cout << max(4, 7) << '\n'; // note: possible inlining

	return 0;
}

int f(int x)
{
	return (x + 1);
}