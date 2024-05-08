#include <iostream>

int main()
{
	const auto b1 = true, b2 = true;

	std::cout <<    !b1 << ' ' << (b1 || b2) << ' ' << (b1  && b2) << std::endl;
	std::cout << not b1 << ' ' << (b1 or b2) << ' ' << (b1 and b2) << std::endl;

	std::cout << (true || (b1 && b2)) << std::endl; // support: вычисления по короткой схеме

	[[maybe_unused]] auto r1 = (!(b1 && b2) == !b1 || !b2); // support: законы де Моргана
	[[maybe_unused]] auto r2 = (!(b1 || b2) == !b1 && !b2);

//  ================================================================================================

	auto x = 1, y = 2;

	std::cout << (!!x != !!y) << std::endl; // support: оператор xor

	std::cout << (    -y) << std::endl;
	std::cout << (    +y) << std::endl;

	std::cout << (x +  y) << std::endl;
	std::cout << (x -  y) << std::endl;
	std::cout << (x *  y) << std::endl;
	std::cout << (x /  y) << std::endl; 
	std::cout << (x %  y) << std::endl;

	std::cout << (x += y) << std::endl;
	std::cout << (x -= y) << std::endl;
	std::cout << (x *= y) << std::endl;
	std::cout << (x /= y) << std::endl;
	std::cout << (x %= y) << std::endl;

	std::cout << (x <  y) << std::endl;
	std::cout << (x >  y) << std::endl;
	std::cout << (x <= y) << std::endl;
	std::cout << (x >= y) << std::endl;
	std::cout << (x == y) << std::endl;
	std::cout << (x != y) << std::endl;

	std::cout << (x++   ) << std::endl;
	std::cout << (x--   ) << std::endl;
	std::cout << (   ++x) << std::endl;
	std::cout << (   --x) << std::endl;

//  ================================================================================================

	x = x + y; y = x - y; x = x - y; // support: задачи Google

//  ================================================================================================

	std::cout << (1   / 2  ) << std::endl;
	std::cout << (1.0 / 2.0) << std::endl;

	std::cout << (1.0 * x / y) << std::endl;

	std::cout << (+1 % +2) << std::endl;
	std::cout << (+1 % -2) << std::endl;
	std::cout << (-1 % +2) << std::endl;
	std::cout << (-1 % -2) << std::endl;

//	x+++++y; // error

//  ================================================================================================

	[[maybe_unused]] auto z = (1 + 4) / (2 + 3);

//	std::cout << (z + ++z) << std::endl; // warning

//  ================================================================================================

	[[maybe_unused]] auto m = 1 + 2 + 3;
	[[maybe_unused]] auto n = x = y = z;

//	std::cout << (++m, ++n) << std::endl; // bad: непонятный синтаксис

	return 0;
}
