#include <iostream>

int main()
{
	const auto b1 = true, b2 = true;

	std::cout <<    !b1 << ' ' << (b1 || b2) << ' ' << (b1  && b2) << std::endl;
	std::cout << not b1 << ' ' << (b1 or b2) << ' ' << (b1 and b2) << std::endl;

	std::cout << (true || (b1 && b2)) << std::endl; // note: см. вычисления по короткой схеме

	[[maybe_unused]] auto law_1 = (!(b1 && b2) == !b1 || !b2);
	[[maybe_unused]] auto law_2 = (!(b1 || b2) == !b1 && !b2);

//  ================================================================================================

	auto x = 1, y = 2;

	std::cout << (!!x != !!y) << std::endl; // note: см. оператор xor

	std::cout << (    -x) << std::endl;
	std::cout << (    +x) << std::endl;

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

	x = x + y; y = x - y; x = x - y; // note: см. собеседование в Google

//  ================================================================================================

	std::cout << (1   / 2  ) << std::endl;
	std::cout << (1.0 / 2.0) << std::endl;

	std::cout << (1.0 * x / y) << std::endl;

	std::cout << (+1 % +2) << std::endl;
	std::cout << (+1 % -2) << std::endl;
	std::cout << (-1 % +2) << std::endl;
	std::cout << (-1 % -2) << std::endl;

//	x+++++y; // error: принцип максимального куска

//  ================================================================================================

	auto z = (1 + 4) / (2 + 3);

//	std::cout << (z + ++z) << std::endl; // bad: неспецифицированный порядок

//  ================================================================================================

	[[maybe_unused]] auto m = 1 + 2 + 3;
	[[maybe_unused]] auto n = x = y = z;

//	std::cout << (++m, ++n) << std::endl; // bad: трудновоспринимаемый синтаксис

	return 0;
}
