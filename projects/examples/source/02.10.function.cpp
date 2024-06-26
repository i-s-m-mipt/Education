#include <iostream>
#include <span>
#include <string>
#include <vector>

//  ================================================================================================

[[nodiscard]] int f(int x);

[[nodiscard]] int g(int x, int y, int z = 1) { return (x + y + z); }

//  ================================================================================================

void extract_data(int * ptr = nullptr)
{
	[[maybe_unused]] auto local_data = (ptr ? *ptr : 42);
} 

//  ================================================================================================

void test_pointers(int * x, const int * y)
{
	if (!x || !y) return;

	++(*x);
//	++(*y); // error
}

void test_references(int & x, [[maybe_unused]] const int & y)
{
	++x;
//	++y; // error
}

//  ================================================================================================

void print_string(const std::string & string)
{
	std::cout << string << std::endl;
}

void print_array(const int * array, std::size_t size)
{
	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << array[i] << (i + 1 == size ? '\n' : ' ');
	}
}

void print_span(std::span < const int > span)
{
	for (const auto element : span) std::cout << element << ' ';

	std::cout << std::endl;
}

void print_vector(const std::vector < int > & vector)
{
	for (const auto element : vector) std::cout << element << ' ';

	std::cout << std::endl;
}

//  ================================================================================================

/*
[[nodiscard]] int * get_dangling_pointer  () { auto local = 42; return &local; } // error
[[nodiscard]] int & get_dangling_reference() { auto local = 42; return  local; } // error
*/

//  ================================================================================================

void h()
{
	       auto x = 42; 
	static auto y = 42;

	std::cout << ++x << ' ' << ++y << std::endl;
}

//  ================================================================================================

[[nodiscard]] inline auto max(int x, int y) { return (x > y ? x : y); }

[[nodiscard]] inline int factorial(int n) 
{ 
	return (n < 2 ? 1 : n * factorial(n - 1)); 
}

//  ================================================================================================

inline void print(bool, bool) { std::cout << "print(bool, bool)" << std::endl; }
inline void print(char, char) { std::cout << "print(char, char)" << std::endl; }

//  ================================================================================================

int main()
{
//	f(42); // error

	[[maybe_unused]] const auto result = g(f(42), f(42));

//  ================================================================================================

	auto x = 42, y = 42;

	test_pointers  (&x, &y); std::cout << x << ' ' << y << std::endl; // output: 43 42
	test_references( x,  y); std::cout << x << ' ' << y << std::endl; // output: 44 42

//  ================================================================================================

	const std::size_t size = 5;

	const int         array_1                [size]{ 1, 2, 3, 4, 5 };
	const int * const array_2 = new const int[size]{ 1, 2, 3, 4, 5 };

	print_array(array_1, size); print_span({ array_1       });
	print_array(array_2, size); print_span({ array_2, size });

	delete[] array_2;

	const std::vector < int > vector { 1, 2, 3, 4, 5 };

	print_vector(vector);

//  ================================================================================================

//	std::cout << *get_dangling_pointer  () << std::endl; // error
//	std::cout <<  get_dangling_reference() << std::endl; // error

	h(); h(); h();

//  ================================================================================================

	std::cout << max(1, 2) << ' ' << factorial(5) << std::endl; // output: 2 120

//	print('a', true); // error

	return 0;
}

//  ================================================================================================

int f(int x) { return (x + 1); } // demo