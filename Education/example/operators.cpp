#include <iostream>

int main()
{
	auto a = true;
	auto b = true;

	std::cout << !a << ' ' << not a << '\n';

	std::cout << (a || b) << ' ' << (a  or b) << '\n';
	std::cout << (a && b) << ' ' << (a and b) << '\n';

	std::cout << (true or a and b) << '\n';

	[[maybe_unused]] auto law_1 = (!(a && b) == !a || !b);
	[[maybe_unused]] auto law_2 = (!(a || b) == !a && !b);

	auto x = 7;
	auto y = 4;

	std::cout << -x << '\n';
	std::cout << +x << '\n';

	std::cout << x + y << '\n';
	std::cout << x - y << '\n';
	std::cout << x * y << '\n';
	std::cout << x / y << '\n';
	std::cout << x % y << '\n';

	std::cout << 7   / 4   << '\n';
	std::cout << 7.0 / 4.0 << '\n';

	std::cout << 1.0 * x / y << '\n';

	std::cout << +7 % +4 << '\n';
	std::cout << +7 % -4 << '\n';
	std::cout << -7 % +4 << '\n';
	std::cout << -7 % -4 << '\n';

	std::cout << (x += y) << '\n';
	std::cout << (x -= y) << '\n';
	std::cout << (x *= y) << '\n';
	std::cout << (x /= y) << '\n';
	std::cout << (x %= y) << '\n';

	std::cout << (x < y) << '\n';
	std::cout << (x > y) << '\n';

	std::cout << (x <= y) << '\n';
	std::cout << (x >= y) << '\n';

	std::cout << (x == y) << '\n';
	std::cout << (x != y) << '\n';

	std::cout << x++ << ' ' << x << '\n';
	std::cout << x-- << ' ' << x << '\n';
	std::cout << ++x << ' ' << x << '\n';
	std::cout << --x << ' ' << x << '\n';

	auto z = (1 + 4) / (2 + 3);

	std::cout << (z + ++z) << '\n';

	auto m = 1 + 2 + 3;
	auto n = x = y = z;

	std::cout << (++m, ++n) << '\n';

	return 0;
}