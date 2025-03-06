#include <iostream>

/////////////////////////////////////////////////////////////////////////////////

int main()
{
    for (auto i = 0uz; i < 5; ++i)
	{
		for (auto j = 0uz; j < 5; ++j)
		{
			std::cout << "main : iteration : i = " << i << " j = " << j << ' ';

			std::cout << "enter \'b\' to break : "; auto x = '\0'; std::cin >> x;
			
			if (x == 'b') 
			{
				goto exit; // support: compiler-explorer.com
			}
		}
	}

	exit:
}