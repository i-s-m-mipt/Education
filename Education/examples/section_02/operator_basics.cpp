#include <iostream>

int main()
{
	auto a = true;
	auto b = true;

	std::cout <<    !a << ' ' << (a || b) << ' ' << (a  && b) << std::endl;
	std::cout << not a << ' ' << (a or b) << ' ' << (a and b) << std::endl;

	std::cout << (true or a and b) << std::endl; // note: short-circuit evaluation

	[[maybe_unused]] auto law_1 = (!(a && b) == !a || !b);
	[[maybe_unused]] auto law_2 = (!(a || b) == !a && !b);

	auto x = 7;
	auto y = 4;

	std::cout << -x << std::endl;
	std::cout << +x << std::endl;

	std::cout << x + y << std::endl;
	std::cout << x - y << std::endl;
	std::cout << x * y << std::endl;
	std::cout << x / y << std::endl; 
	std::cout << x % y << std::endl;

	std::cout << 7   / 4   << std::endl; // note: integer  division
	std::cout << 7.0 / 4.0 << std::endl; // note: floating division

	std::cout << 1.0 * x / y << std::endl; // good: 1.0 instead of static_cast

	std::cout << +7 % +4 << std::endl; // note: result is +3
	std::cout << +7 % -4 << std::endl; // note: result is +3
	std::cout << -7 % +4 << std::endl; // note: result is -3
	std::cout << -7 % -4 << std::endl; // note: result is -3

	std::cout << (x += y) << std::endl; // good: x += y instead of x = x + y
	std::cout << (x -= y) << std::endl; // good: x -= y instead of x = x - y
	std::cout << (x *= y) << std::endl; // good: x *= y instead of x = x * y
	std::cout << (x /= y) << std::endl; // good: x /= y instead of x = x / y
	std::cout << (x %= y) << std::endl; // good: x %= y instead of x = x % y

	std::cout << (x <  y) << std::endl;
	std::cout << (x >  y) << std::endl;

	std::cout << (x <= y) << std::endl;
	std::cout << (x >= y) << std::endl;

	std::cout << (x == y) << std::endl;
	std::cout << (x != y) << std::endl;

	std::cout << x++ << ' ' << x << std::endl; // good: x++ instead of x += 1
	std::cout << x-- << ' ' << x << std::endl; // good: x-- instead of x -= 1
	std::cout << ++x << ' ' << x << std::endl; // good: ++x instead of x += 1
	std::cout << --x << ' ' << x << std::endl; // good: --x instead of x -= 1

	auto z = (1 + 4) / (2 + 3); // note: unspecified operands evaluation order

//	std::cout << (z + ++z) << std::endl; // bad: unspecified behavior

	auto m = 1 + 2 + 3; // note: left to right associativity
	auto n = x = y = z; // note: right to left associativity

//	std::cout << (++m, ++n) << std::endl; // bad: inconvenient comma operator syntax

	return 0;
}