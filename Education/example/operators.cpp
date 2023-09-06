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
	
	std::cout << a << ' ' << b << '\n';

	int c = a++;

	std::cout << a << ' ' << c << '\n';

	a = 1 + 2 + 3;

	a = b = c;

	std::cout << 7 / 4 << '\n';

	std::cout << 7.0 / 4.0 << '\n';

	std::cout << 1.0 * b / c << '\n';

	bool b_1 = (b == c);
	bool b_2 = (b <= c);

	return 0;
}