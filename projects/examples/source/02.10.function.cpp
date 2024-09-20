#include <algorithm>
#include <cassert>
#include <iostream>
#include <span>
#include <string>
#include <vector>

//  ================================================================================================

[[nodiscard]] int f(int x);

[[nodiscard]] int g(int x, int y, int z = 3) 
{ 
	return (x + y + z); 
}

//  ================================================================================================

void update(int * x, [[maybe_unused]] const int * y) { if (x && y) *x = *y; }
void update(int & x, [[maybe_unused]] const int & y) {              x =  y; }

//  ================================================================================================

[[nodiscard]] bool test(const std::string & string) 
{
	return std::ranges::is_sorted(string);
}

[[nodiscard]] bool test(const int * array, std::size_t size)
{
	return std::ranges::is_sorted(array, array + size);
}

[[nodiscard]] bool test(std::span < const int > span)
{
	return std::ranges::is_sorted(span);
}

[[nodiscard]] bool test(const std::vector < int > & vector)
{
	return std::ranges::is_sorted(vector);
}

//  ================================================================================================

//  [[nodiscard]] int * get_dangling_ptr() { auto local = 1; return &local; } // error
//  [[nodiscard]] int & get_dangling_ref() { auto local = 1; return  local; } // error

//  ================================================================================================

void h()
{
	static auto s = 1; std::cout << "s = " << s++ << std::endl;
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
	auto x = 1, y = 2;

//	f(x); // error

	assert(g(f(x), f(y)) == 6); // support: compiler-explorer.com

//  ================================================================================================

	x = 1; y = 2; update(&x, &y); assert(x == 2 && y == 2);
	x = 1; y = 2; update( x,  y); assert(x == 2 && y == 2);

//  ================================================================================================

	assert(test(std::string("aaa")));

	const std::size_t size = 5;

	const int         array_1                [size] { 1, 2, 3, 4, 5 };
	const int * const array_2 = new const int[size] { 1, 2, 3, 4, 5 };

	assert(test(  array_1, size  )); 
	assert(test(  array_2, size  )); 
	assert(test({ array_1       }));
	assert(test({ array_2, size })); 
	
	delete[] array_2;

	assert(test(std::vector < int > ({ 1, 2, 3, 4, 5 })));

//	assert(test(1)); // error

//  ================================================================================================

//	assert(*get_dangling_ptr() == 1); // error
//	assert( get_dangling_ref() == 1); // error

	h(); h(); h();

//  ================================================================================================

	assert(max(1, 2) == 2 && factorial(5) == 120); // support: compiler-explorer.com

	return 0;
}

//  ================================================================================================

[[nodiscard]] int f(int x) { return x; }