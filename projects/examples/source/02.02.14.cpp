////////////////////////////////////////////////////////////////////////////

#include <iostream>

////////////////////////////////////////////////////////////////////////////

int main()
{
	auto x = 0;

//  ------------------------------------------------------------------------

	while (x > 0)
	{
		std::cout << "main : iteration (1) : enter int x : "; std::cin >> x;
	}

//  ------------------------------------------------------------------------

	while (true)
	{
		std::cout << "main : iteration (2) : enter int x : "; std::cin >> x;

	//  --------------------------------------------------------------------

		if (x == 0)
		{
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////