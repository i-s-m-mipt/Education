#include <iostream>

int main()
{
	bool x = true;
	bool y = false;

	bool z = (x || y) && !y;

	int a = -42;

	a = a + 42;

	a += 42;

	int b = ++a;
	
	std::cout << a << ' ' << b << std::endl;

	int c = a++;

	std::cout << a << ' ' << c << std::endl;

	a = 1 + 2 + 3;

	a = b = c;

	std::cout << 7 / 4 << std::endl;

	std::cout << 7.0 / 4.0 << std::endl;

	std::cout << 1.0 * b / c << std::endl;

	bool b_1 = (b == c);
	bool b_2 = (b <= c);

	return 0;
}