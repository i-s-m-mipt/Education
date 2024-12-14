#include <cassert>
#include <cstddef>
#include <iostream>
#include <span>
#include <string>
#include <utility>
#include <vector>

//  ================================================================================================

[[nodiscard]] auto test_v1(int x);

[[nodiscard]] auto test_v1(int x) 
{
	return x; 
}

void test_v2([[maybe_unused]] int x, [[maybe_unused]] int y = 0) 
{ 
	std::cout << "test_v2\n"; 
}

//  ================================================================================================

void test_v3(int * x, const int * y) { if (x && y) { *x = *y; } }
void test_v4(int & x, const int & y) {                x =  y;   }

//  ================================================================================================

void test_v5(const int * , std::size_t)
{
	std::cout << "test_v5 (2)\n";
}

void test_v5(std::span < const int > )
{
	std::cout << "test_v5 (3)\n";
}

void test_v5(const std::vector < int > &)
{
	std::cout << "test_v5 (4)\n";
}

void test_v5(const std::string &) 
{
	std::cout << "test_v5 (1)\n";
}

//  ================================================================================================

//  auto   test_v6() { auto x = 1; return &x; } // error
//  auto & test_v7() { auto x = 1; return  x; } // error

//  ================================================================================================

const auto & test_v8()
{
	static auto state = 0; // support: compiler-explorer.com

	return ++state;
}

//  ================================================================================================

inline auto max_v1(int x, int y)
{ 
	return x > y ? x : y; 
}

__attribute__ ((__noinline__)) auto max_v2(int x, int y)
{
	return x > y ? x : y;
}

//  ================================================================================================

int main()
{
	[[maybe_unused]] auto result = test_v1(1);

	std::ignore = test_v1(1);

//	test_v1(1); // error

	test_v2(1); // support: compiler-explorer.com

//  -------------------------------------------------------------------

	auto x1 = 1, y1 = 2; test_v3(&x1, &y1); assert(x1 == 2 && y1 == 2);
	auto x2 = 1, y2 = 2; test_v4( x2,  y2); assert(x2 == 2 && y2 == 2);

//  -------------------------------------------------------------------

	int array_1[5]{};

	test_v5(array_1, std::size(array_1));

	test_v5(std::span < const int > (array_1));

	auto size = 5uz;

	auto array_2 = new int[size]{};

	test_v5(array_2, size); 

	test_v5(std::span < const int > (array_2, size)); 
	
	delete[] array_2;

	test_v5(std::vector < int > (size, 0));

	test_v5("aaaaa");

//	test_v5(1); // error

//  ---------------------------------

//	assert(*test_v6() == 1); // error
//	assert( test_v7() == 1); // error

	assert( test_v8() == 1);
	assert( test_v8() == 2);
	assert( test_v8() == 3);

//  ---------------------------

	volatile auto x = 1, y = 2;

	assert(max_v1(x, y) == 2); // support: compiler-explorer.com
	assert(max_v2(x, y) == 2); // support: compiler-explorer.com
	assert(max_v1(1, 2) == 2); // support: compiler-explorer.com
	assert(max_v2(1, 2) == 2); // support: compiler-explorer.com
}