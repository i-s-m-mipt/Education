#include <iostream>

int main()
{
	const auto b1 = true, b2 = false; // support: std::boolalpha

	std::cout << (   !b1) << ' ' << (b1 || b2) << ' ' << (b1 &&  b2) << std::endl; // output: 0 1 0
	std::cout << (not b1) << ' ' << (b1 or b2) << ' ' << (b1 and b2) << std::endl; // output: 0 1 0

//  ================================================================================================

	std::cout << (b1 || (b1 != b2)) << std::endl; // output: 1; detail: XOR
	std::cout << (b2 && (b1 != b2)) << std::endl; // output: 0; detail: XOR

//  ================================================================================================

	[[maybe_unused]] auto proof_1 = (!(b1 && b2) == (!b1 || !b2));
	[[maybe_unused]] auto proof_2 = (!(b1 || b2) == (!b1 && !b2));

//  ================================================================================================

	auto x = 1, y = 2;

	std::cout << (+x) << ' ' << (-x) << std::endl; // output: +1 -1
	std::cout << (+y) << ' ' << (-y) << std::endl; // output: +2 -2

//  ================================================================================================

	std::cout << (x +  y) << std::endl; // output: +3
	std::cout << (x -  y) << std::endl; // output: -1
	std::cout << (x *  y) << std::endl; // output: +2
	std::cout << (x /  y) << std::endl; // output: +0
	std::cout << (x %  y) << std::endl; // output: +1

//  ================================================================================================

	std::cout << (x += y) << std::endl; // output: +3; detail: x = x + y
	std::cout << (x -= y) << std::endl; // output: +1; detail: x = x - y
	std::cout << (x *= y) << std::endl; // output: +2; detail: x = x * y
	std::cout << (x /= y) << std::endl; // output: +1; detail: x = x / y
	std::cout << (x %= y) << std::endl; // output: +1; detail: x = x % y

//  ================================================================================================

	std::cout << (  ++ x) << std::endl; // output: +2; detail: x = x + 1
	std::cout << (  -- x) << std::endl; // output: +1; detail: x = x - 1
	std::cout << (x ++  ) << std::endl; // output: +1; detail: x = x + 1
	std::cout << (x --  ) << std::endl; // output: +2; detail: x = x - 1

//  ================================================================================================

	std::cout << (x <  y) << std::endl; // output: 1
	std::cout << (x >  y) << std::endl; // output: 0
	std::cout << (x <= y) << std::endl; // output: 1
	std::cout << (x >= y) << std::endl; // output: 0
	std::cout << (x == y) << std::endl; // output: 0
	std::cout << (x != y) << std::endl; // output: 1
	
//  ================================================================================================

	std::cout << (!!x != !!y) << std::endl; // output: 0; detail: XOR

	const auto d1 = 1.0, d2 = 2.0;

	std::cout << (d1 / d2) << std::endl; // output: +0.5

	std::cout << ( x %  y) << std::endl; // output: +1
	std::cout << ( x % -y) << std::endl; // output: +1
	std::cout << (-x %  y) << std::endl; // output: -1
	std::cout << (-x % -y) << std::endl; // output: -1

//	x+++++y; // error

	x = x + y; y = x - y; x = x - y; // support: Google

//  ================================================================================================

	[[maybe_unused]] auto z = (1 + 4) / (2 + 3);

//	std::cout << (z + ++z) << std::endl; // warning

	[[maybe_unused]] auto m = 1 + 2 + 3;
	[[maybe_unused]] auto n = x = y = z;

//	std::cout << (++m, ++n) << std::endl; // bad

	return 0;
}
