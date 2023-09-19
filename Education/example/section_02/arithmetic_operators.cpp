#include <iostream>

int main()
{
	auto a = true;
	auto b = true;

	std::cout <<    !a << ' ' << (a || b) << ' ' << (a  && b) << '\n';
	std::cout << not a << ' ' << (a or b) << ' ' << (a and b) << '\n';

	std::cout << (true or a and b) << '\n'; // note: short-circuit evaluation

	[[maybe_unused]] auto law_1 = (!(a && b) == !a || !b);
	[[maybe_unused]] auto law_2 = (!(a || b) == !a && !b);

	auto x = 7;
	auto y = 4;

	std::cout << -x << '\n';
	std::cout << +x << '\n';

	std::cout << x + y << '\n';
	std::cout << x - y << '\n';
	std::cout << x * y << '\n';
	std::cout << x / y << '\n'; // note: integer division
	std::cout << x % y << '\n';

	std::cout << 7   / 4   << '\n';
	std::cout << 7.0 / 4.0 << '\n';

	std::cout << 1.0 * x / y << '\n'; // good: 1.0 instead of static_cast

	std::cout << +7 % +4 << '\n'; // note: result is +3
	std::cout << +7 % -4 << '\n'; // note: result is +3
	std::cout << -7 % +4 << '\n'; // note: result is -3
	std::cout << -7 % -4 << '\n'; // note: result is -3

	std::cout << (x += y) << '\n'; // good: x += y instead of x = x + y
	std::cout << (x -= y) << '\n'; // good: x -= y instead of x = x - y
	std::cout << (x *= y) << '\n'; // good: x *= y instead of x = x * y
	std::cout << (x /= y) << '\n'; // good: x /= y instead of x = x / y
	std::cout << (x %= y) << '\n'; // good: x %= y instead of x = x % y

	std::cout << (x < y) << '\n';
	std::cout << (x > y) << '\n';

	std::cout << (x <= y) << '\n';
	std::cout << (x >= y) << '\n';

	std::cout << (x == y) << '\n';
	std::cout << (x != y) << '\n';

	std::cout << x++ << ' ' << x << '\n'; // good: x++ instead of x += 1
	std::cout << x-- << ' ' << x << '\n'; // good: x-- instead of x -= 1
	std::cout << ++x << ' ' << x << '\n'; // good: ++x instead of x += 1
	std::cout << --x << ' ' << x << '\n'; // good: --x instead of x -= 1

	auto z = (1 + 4) / (2 + 3); // note: unspecified operands evaluation order

//	std::cout << (z + ++z) << '\n'; // bad: unspecified behavior

	auto m = 1 + 2 + 3; // note: left to right associativity
	auto n = x = y = z; // note: right to left associativity

//	std::cout << (++m, ++n) << '\n'; // bad: inconvenient comma operator syntax

	return 0;
}