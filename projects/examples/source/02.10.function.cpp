#include <cassert>
#include <iostream>
#include <span>
#include <string>
#include <vector>

//  ================================================================================================

[[nodiscard]] int f(int x);

[[nodiscard]] int g(int x, int y, int z = 1) 
{ 
	return (x + y + z); 
}

//  ================================================================================================

void extract_data(int * ptr = nullptr)
{
	[[maybe_unused]] auto local_data = (ptr ? *ptr : 1);
} 

//  ================================================================================================

void test(int * x, const int * y)
{
	if (!x || !y) return;

	++(*x);
//	++(*y); // error
}

void test(int & x, [[maybe_unused]] const int & y)
{
	++x;
//	++y; // error
}

//  ================================================================================================

void test(const std::string & string) 
{
	assert(std::size(string) != 0);
}

//  ================================================================================================

void test(const int * array, std::size_t size)
{
	for (std::size_t i = 1; i < size; ++i)
	{
		assert(array[i] == array[i-1] + 1);
	}
}

//  ================================================================================================

void test(std::span < const int > span)
{
	for (std::size_t i = 1; i < std::size(span); ++i)
	{
		assert(span[i] == span[i-1] + 1);
	}
}

//  ================================================================================================

void test(const std::vector < int > & vector)
{
	for (std::size_t i = 1; i < std::size(vector); ++i)
	{
		assert(vector[i] == vector[i-1] + 1);
	}
}

//  ================================================================================================

/*
[[nodiscard]] int * get_dangling_ptr() { auto local = 1; return &local; } // error
[[nodiscard]] int & get_dangling_ref() { auto local = 1; return  local; } // error
*/

//  ================================================================================================

void h()
{
	static auto x = 1; 
	
	std::cout << "x = " << x++ << std::endl;
}

//  ================================================================================================

[[nodiscard]] inline auto max(int x, int y) 
{ 
	return (x > y ? x : y); 
}

[[nodiscard]] inline int factorial(int n) 
{ 
	return (n < 2 ? 1 : n * factorial(n - 1)); 
}

//  ================================================================================================

int main()
{
//	f(1); // error

	[[maybe_unused]] const auto result = g(f(1), f(1));

//  ================================================================================================

	auto x = 1, y = 1;

	test(&x, &y); assert(x == 2 && y == 1);
	test( x,  y); assert(x == 3 && y == 1);

//  ================================================================================================

	const std::size_t size = 5;

	const int         array_1                [size] { 1, 2, 3, 4, 5 };
	const int * const array_2 = new const int[size] { 1, 2, 3, 4, 5 };

	test(  array_1, size  ); 
	test(  array_2, size  ); 
	test({ array_1       });
	test({ array_2, size }); 
	
	delete[] array_2;

	test(std::vector < int > { 1, 2, 3, 4, 5 });

//	test(1); // error

//  ================================================================================================

//	assert(*get_dangling_ptr() == 1); // error
//	assert( get_dangling_ref() == 1); // error

	h(); h(); h();

//  ================================================================================================

	assert(max(1, 2) == 2 && factorial(5) == 120);

	return 0;
}

//  ================================================================================================

[[nodiscard]] int f(int x) { return x; }