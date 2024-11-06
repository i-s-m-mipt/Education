#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

//  ================================================================================================

struct Entity
{
	void test() const
	{ 
		[this](){ std::clog << "Entity::test : data = " << data << '\n'; }(); 
	}

	int data = 0;
};

//  ================================================================================================

int main()
{
	auto lambda_1 = [](){}; // support: cppinsights.io

	auto lambda_2 = [](auto x) constexpr noexcept { return x; };

	std::cout << "typeid(lambda_1).name() = " << typeid(lambda_1).name() << '\n';
	std::cout << "typeid(lambda_2).name() = " << typeid(lambda_2).name() << '\n';

//  ================================================================================================

	auto x = 1, y = 2, z = 0;

	[x, y, &z]()         { z = x + y; }();
	[x, y,  z]() mutable { z = x + y; }();

	assert(z == 3);

//	[&](){ z = x + y; }(); // bad

//  ================================================================================================

	auto unique_ptr_1 = std::make_unique < int > (1);

	[unique_ptr_2 = std::move(unique_ptr_1)](){ assert(*unique_ptr_2 == 1); }(); 

//  ================================================================================================

	std::array < std::function < int(int, int) > , 5 > functions;

	functions[0] = [](auto x, auto y){ return x + y; };
	functions[1] = [](auto x, auto y){ return x - y; };
	functions[2] = [](auto x, auto y){ return x * y; };
	functions[3] = [](auto x, auto y){ return x / y; };
	functions[4] = [](auto x, auto y){ return x % y; };

	assert(functions.at(0)(x, y) == (x + y));

//  ================================================================================================

	auto lambda_3 = [] < typename T > (T x, T y){ return x + y; };

	lambda_3(1, 2);

//	lambda_3(1, 2.0); // error

//  ================================================================================================

	std::vector < int > vector(5, 0);

	auto lambda_4 = [z](auto & x){        x += z ; };
	auto lambda_5 = [z](auto   x){ assert(x == z); };

	std::ranges::for_each(              vector , lambda_4);
	std::ranges::for_each(std::as_const(vector), lambda_5);

//  ================================================================================================

	auto lambda_6 = [](auto lhs, auto rhs){ return lhs > rhs; };

	std::set < int, decltype(lambda_6) > set { 5, 4, 3, 2, 1 };

	for (auto element : set) 
	{
		std::cout << element << ' ';
	}

	std::cout << std::endl;
}