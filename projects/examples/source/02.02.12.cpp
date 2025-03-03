#include <iostream>

//////////////////////////////////////////////////////////////////////////

int main()
{
    for (auto i = 0uz; i < 5; ++i)
	{
		std::cout << "main : iteration (1) : i = " << i << ' ';

		std::cout << "enter \'b\' to break : "; char x = 0; std::cin >> x;
			
		if (x == 'b') 
		{
			break; // support: compiler-explorer.com
		}
	}

//  ----------------------------------------------------------------------

    for (;;)
	{
		std::cout << "main : iteration (2) : ";

		std::cout << "enter \'b\' to break : "; char x = 0; std::cin >> x;
			
		if (x == 'b') 
		{
			break;
		}
	}
}