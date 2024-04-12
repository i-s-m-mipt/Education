#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

class C
{
public:

	void f() const { [this](){std::cout << m_data << std::endl; }(); } // note: this captured

private:

	const int m_data = 42;

}; // class C

int main()
{
	constexpr auto lambda = [](){}; // note: lambda expression, look at cppinsights.io

	std::cout << typeid(lambda).name() << std::endl; // note: unique closure type

	auto z1 = 0, z2 = 0;

	[&z1, z2](auto x)         { z1 = z2 + x; }(42);
	[ z1, z2](auto x) mutable { z1 = z2 + x; }(42);

	assert(z1 == 42);

//	[&](auto x){ z1 = z2 + x; }(42); // bad: default capture by reference

	auto unique_pointer = std::make_unique < int > (42);

	[unique_pointer = std::move(unique_pointer)](){ assert(*unique_pointer == 42); }(); 

	std::array < std::function < int(int, int) > , 4 > operations;

	operations[0] = [](auto x, auto y){ return (x + y); };
	operations[1] = [](auto x, auto y){ return (x - y); };
	operations[2] = [](auto x, auto y){ return (x * y); };
	operations[3] = [](auto x, auto y){ return (x / y); };

	constexpr auto x = 1, y = 2;

	assert(operations.at(0)(x, y) == (x + y));

	constexpr auto templated_lambda = [] < typename T > (T x, T y) { return (x + y); };

	templated_lambda(100, 200);
	templated_lambda(1.0, 2.0);
//	templated_lambda(100, 2.0); // error: different types

	constexpr std::size_t size = 5;

	std::vector < int > vector(size, 0);

	std::ranges::for_each(              vector , [z1](auto & x){        x += z1 ; }); // note: modify elements in range
	std::ranges::for_each(std::as_const(vector), [z1](auto   x){ assert(x == z1); }); // note: verify elements in range

	const std::set < int, decltype([](auto lhs, auto rhs){ return (lhs > rhs); }) > set = { 1, 4, 2, 5, 3 };

	for (const auto element : set) std::cout << element << ' ';

	std::cout << std::endl;

	return 0;
}