#include <iostream>

//////////////////////////////////////////////////////////////

int main()
{
	char x = 0;

//  ----------------------------------------------------------

	while (x != 'b')
	{
		std::cout << "main : iteration (1) : ";

		std::cout << "enter \'b\' to break : "; std::cin >> x;
	}

//  ----------------------------------------------------------

	while (1)
	{
		std::cout << "main : iteration (2) : ";

		std::cout << "enter \'b\' to break : "; std::cin >> x;
	}
}