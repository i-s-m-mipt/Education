#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

int main()
{
	auto lambda = [](){};

	std::cout << typeid(lambda).name() << std::endl;

	auto a = 0; // note: internal state, see reference arguments
	auto b = 1;

	[&a, b](auto c)         { a = b + c; }(2);
	[ a, b](auto c) mutable { a = b + c; }(2);

	assert(a == 3);

	std::array < std::function < int(int, int) > , 4 > operations;

	operations[0] = [](auto x, auto y){ return (x + y); };
	operations[1] = [](auto x, auto y){ return (x - y); };
	operations[2] = [](auto x, auto y){ return (x * y); };
	operations[3] = [](auto x, auto y){ return (x / y); };

	auto x = 8;
	auto y = 4;

	assert(operations.at(1)(x, y) == (x - y));

	const std::size_t size = 5;

	std::vector < int > v(size, 0);

	std::for_each(std::begin(v), std::end(v), [a](auto & x) {        x += a ; });
	std::for_each(std::begin(v), std::end(v), [a](auto   x) { assert(x == a); });

	return 0;
}