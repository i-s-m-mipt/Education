////////////////////////////////////////////////////////////

#include <iostream>

////////////////////////////////////////////////////////////

int main()
{
	auto x = 0;

//  --------------------------------------------------------

    for (auto i = 0uz; i < 5; ++i)
	{
		std::cout << "main : i = " << i << '\n';

	//  ----------------------------------------------------

		std::cout << "main : enter int x : "; std::cin >> x;

	//  ----------------------------------------------------
			
		if (x == 0)
		{
			break; // support : compiler-explorer.com
		}
	}

//  --------------------------------------------------------

    for (;;)
	{
		std::cout << "main : enter int x : "; std::cin >> x;

	//  ----------------------------------------------------
			
		if (x == 0)
		{
			break;
		}
	}
}

////////////////////////////////////////////////////////////