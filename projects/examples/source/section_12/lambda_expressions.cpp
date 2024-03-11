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

	int m_data = 0;

}; // class C

int main()
{
	auto lambda = [](){}; // note: lambda expression, look at cppinsights.io

	std::cout << typeid(lambda).name() << std::endl; // note: unique closure type

	auto a = 0; // note: internal state, see reference arguments
	auto b = 1;

	[&a, b](auto c)         { a = b + c; }(2);
	[ a, b](auto c) mutable { a = b + c; }(2);

	assert(a == 3);

//	[&](auto c){ a = b + c; }(2); // bad: default capture by reference

	auto up = std::make_unique < int > (42);

	[up = std::move(up)](){ assert(*up == 42); }(); // note: capture by move

	std::array < std::function < int(int, int) > , 4 > operations;

	operations[0] = [](auto x, auto y){ return (x + y); };
	operations[1] = [](auto x, auto y){ return (x - y); };
	operations[2] = [](auto x, auto y){ return (x * y); };
	operations[3] = [](auto x, auto y){ return (x / y); };

	auto x = 8;
	auto y = 4;

	assert(operations.at(1)(x, y) == (x - y));

	auto templated_lambda = [] < typename T > (T x, T y) { return (x + y); };

	templated_lambda(100, 200);
	templated_lambda(1.0, 2.0);
//	templated_lambda(100, 2.0); // error: different types

	const std::size_t size = 5;

	std::vector < int > vector(size, 0);

	std::ranges::for_each(              vector , [a](auto & x){        x += a ; });
	std::ranges::for_each(std::as_const(vector), [a](auto   x){ assert(x == a); });

	std::set < int, decltype([](auto lhs, auto rhs){ return (lhs > rhs); }) > set = { 1, 4, 2, 5, 3 };

	for (auto element : set) std::cout << element << ' '; // note: outputs 5 4 3 2 1

	std::cout << std::endl;

	return 0;
}