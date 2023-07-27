#include <iostream>

void f(int x)
{
	switch (x)
	{
	[[unlikely]] case 0:
	{
		std::cout << "case 0" << std::endl;
		[[fallthrough]];
	}
	case 1:
	{
		std::cout << "case 1" << std::endl;
		break;
	}
	[[likely]] case 2:
	{
		std::cout << "case 2" << std::endl;
		break;
	}
	default:
	{
		std::cout << "default" << std::endl;
		break;
	}
	}
}

int main()
{
	f(0);
	f(1);
	f(2);
	f(3);

	system("pause");

	return 0;
}