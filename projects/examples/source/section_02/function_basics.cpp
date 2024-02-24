#include <iostream>
#include <span>
#include <string>
#include <vector>

[[nodiscard]] int f(int x); // note: forward declaration

[[nodiscard]] int g(int x, int y, int z = 1) // note: trailing default arguments
{
	return (x + y + z);
}

void set_code(int * code = nullptr) // good: nullptr as default argument
{
	[[maybe_unused]] auto local_code = (code ? *code : 1234);
} 

void test_pointers(int * x, const int * y) // note: demo only
{
	if (!x || !y)
	{
		return;
	}

	++(*x);
//	++(*y); // error: pointer to constant value
}

void test_references(int & x, [[maybe_unused]] const int & y) // note: demo only
{
	++x;
//	++y; // error: constant reference
}

void print_string(const std::string & string) // good: constant reference for read-only
{
	std::cout << string << std::endl;
}

void print_array(const int * array, std::size_t size) // note: array size as additional argument
{
	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << array[i] << (i + 1 == size ? '\n' : ' ');
	}
}

void print_span(std::span < int > span) // good: std::span knows its size as all* containers
{
	const auto size = span.size();

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << span[i] << (i + 1 == size ? '\n' : ' ');
	}
}

void print_vector(const std::vector < int > & vector) // good: std::vector knows its size
{
	const auto size = vector.size();

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << vector[i] << (i + 1 == size ? '\n' : ' ');
	}
}

/*
[[nodiscard]] int * get_dangling_pointer()
{
	auto d = 42; // good: static const auto d = 42;

	return &d; // warning: dangling pointer to non-static local variable
}
*/

/*
[[nodiscard]] int & get_dangling_reference()
{
	auto d = 42; // good: static const auto d = 42;

	return d; // warning: dangling reference to non-static local variable
}
*/

void h()
{
	auto x = 0; // note: ordinary local variable

	static auto y = 0; // note: once initialized static variable

	std::cout << ++x << ' ' << ++y << std::endl;

	return;
}

void print(bool   x) { std::cout << x << std::endl; } // note: overloaded function
void print(char   x) { std::cout << x << std::endl; } // note: overloaded function
void print(double x) { std::cout << x << std::endl; } // note: overloaded function

unsigned int factorial(unsigned int n)
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

	test_pointers  (&x, &y); std::cout << x << ' ' << y << std::endl;
	test_references( x,  y); std::cout << x << ' ' << y << std::endl;

	const std::size_t size = 5;

	int   array_1          [size]{ 1, 2, 3, 4, 5 };
	int * array_2 = new int[size]{ 1, 2, 3, 4, 5 };

	print_array(array_1, size); print_span({ array_1       });
	print_array(array_2, size); print_span({ array_2, size });

	delete[] array_2;

	std::vector < int > vector = { 1, 2, 3, 4, 5 };

	print_vector(vector); // good: no copying of big object

//	std::cout << *get_dangling_pointer  () << std::endl; // bad: undefined behavior
//	std::cout <<  get_dangling_reference() << std::endl; // bad: undefined behavior

	h(); // note: outputs 1 1
	h(); // note: outputs 1 2
	h(); // note: outputs 1 3

	print(true);
	print(3.14);
//	print(1234); // error: ambiguous function overloading

	std::cout << factorial(5) << std::endl;

	std::cout << max(4, 7) << std::endl; // note: possible inlining

	return 0;
}

int f(int x) // note: separate definition only for demonstration here
{
	return (x + 1);
}