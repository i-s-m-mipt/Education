#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <vector>

int main()
{
	auto lambda = [](){};

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

	std::vector < int > v(size, 0);

	std::for_each(std:: begin(v), std:: end(v), [a](auto & x) {        x += a ; });
	std::for_each(std::cbegin(v), std::cend(v), [a](auto   x) { assert(x == a); });

	std::set < int, decltype([](auto lhs, auto rhs){ return (lhs > rhs); }) > set({ 1, 4, 2, 5, 3 });

	for (auto iterator = std::cbegin(set); iterator != std::cend(set); ++iterator)
	{
		std::cout << *iterator << ' '; // note: outputs 5 4 3 2 1
	}

	return 0;
}