#include <iostream>

////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto x = 0;

//  ----------------------------------------------------------------------------

    for (auto i = 0uz; i < 5; ++i)
	{
		for (auto j = 0uz; j < 5; ++j)
		{
			std::cout << "main : iteration : i = " << i << " j = " << j << '\n';

			std::cout << "main : iteration : enter int : "; std::cin >> x;
			
			if (x == 0) 
			{
				goto exit; // support : compiler-explorer.com
			}
		}
	}

//  ----------------------------------------------------------------------------

	exit:
}