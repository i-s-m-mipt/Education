#include <iostream>

int main()
{
	const auto b1 = true, b2 = true;

	std::cout <<    !b1 << ' ' << (b1 || b2) << ' ' << (b1  && b2) << std::endl;
	std::cout << not b1 << ' ' << (b1 or b2) << ' ' << (b1 and b2) << std::endl;

	std::cout << (true || (b1 && b2)) << std::endl; // note: short-circuit evaluation

	[[maybe_unused]] auto law_1 = (!(b1 && b2) == !b1 || !b2);
	[[maybe_unused]] auto law_2 = (!(b1 || b2) == !b1 && !b2);

	std::cout << (b1 != b2) << std::endl; // note: b1 xor b2 for booleans

//  ================================================================================================

	auto x = 1, y = 2;

//  ================================================================================================

	std::cout << (!!x != !!y) << std::endl; // note: x xor y for non-booleans

	std::cout << (    -x) << std::endl;
	std::cout << (    +x) << std::endl;

	std::cout << (x +  y) << std::endl;
	std::cout << (x -  y) << std::endl;
	std::cout << (x *  y) << std::endl;
	std::cout << (x /  y) << std::endl; 
	std::cout << (x %  y) << std::endl;

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

	std::cout << (x++   ) << std::endl; // good: x++ instead of x += 1
	std::cout << (x--   ) << std::endl; // good: x-- instead of x -= 1
	std::cout << (   ++x) << std::endl; // good: ++x instead of x += 1
	std::cout << (   --x) << std::endl; // good: --x instead of x -= 1

//  ================================================================================================

	x = x + y; y = x - y; x = x - y; // note: Google interview, solution 1

//  ================================================================================================

	std::cout << (1   / 2  ) << std::endl; // note: integer  division
	std::cout << (1.0 / 2.0) << std::endl; // note: floating division

	std::cout << (1.0 * x / y) << std::endl; // good: 1.0 instead of static_cast

	std::cout << (+1 % +2) << std::endl; // note: result is +1
	std::cout << (+1 % -2) << std::endl; // note: result is +1
	std::cout << (-1 % +2) << std::endl; // note: result is -1
	std::cout << (-1 % -2) << std::endl; // note: result is -1

//	x+++++y; // error: maximum piece principle, write as (x++)+(++y);

//  ================================================================================================

	auto z = (1 + 4) / (2 + 3); // note: unspecified operands evaluation order

//	std::cout << (z + ++z) << std::endl; // bad: unspecified behavior

//  ================================================================================================

	[[maybe_unused]] auto m = 1 + 2 + 3; // note: left to right associativity
	[[maybe_unused]] auto n = x = y = z; // note: right to left associativity

//	std::cout << (++m, ++n) << std::endl; // bad: inconvenient comma operator syntax

	return 0;
}
