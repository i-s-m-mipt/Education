#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		for (auto i = 0uz; i < 5; ++i) // support: compiler-explorer.com
		{
			std::cout << "main : iteration (01) : i = " << i << '\n';
		}
	}

//  ---------------------------------------------------------------------------------

	{
		for (auto i = 0uz, j = 0uz; i < 5; ++i, j += 2)
		{
			std::cout << "main : iteration (02) : i = " << i << " j = " << j << '\n';
		}
	}

//  ---------------------------------------------------------------------------------

	{
		for (auto i = 0uz; [[maybe_unused]] auto x = i < 5; ++i)
		{
			std::cout << "main : iteration (03) : i = " << i << '\n';
		}
	}
	

//  ---------------------------------------------------------------------------------

	{
//		for (auto i = 5uz; i >= 0; --i); // error
//		{
//			std::cout << "main : iteration (04) : i = " << i << '\n';
//		}
	}

//  ---------------------------------------------------------------------------------

	{
		for (auto i = 0uz; i < 5; ++i)
		{
			std::cout << "main : iteration (05) : i = " << i << '\n';
			
			continue; // support: compiler-explorer.com

			std::cout << "main : iteration (05) : i = " << i << '\n';
		}
	}
	
//  ---------------------------------------------------------------------------------

	{
		for (auto i = 0uz; i < 5; ++i)
		{
			std::cout << "main : iteration (06) : i = " << i << ' ';

			std::cout << "enter \'b\' to break : "; char x = 0; std::cin >> x;
			
			if (x == 'b') 
			{
				break; // support: compiler-explorer.com
			}
		}
	}
	
//  ---------------------------------------------------------------------------------

	{
		for (auto i = 0uz; i < 5; ++i)
		{
			for (auto j = 0uz; j < 5; ++j)
			{
				for (auto k = 0uz; k < 5; ++k)
				{
					std::cout << "main : iteration (07) : ";
					
					std::cout << "i = " << i << " j = " << j << " k = " << k << ' ';

					std::cout << "enter \'b\' to break : "; char x = 0; std::cin >> x;
			
					if (x == 'b') 
					{
						goto exit; // support: compiler-explorer.com
					}
				}
			}
		}

		exit:
	}
	
//  ---------------------------------------------------------------------------------

	{
		for (;;)
		{
			std::cout << "main : iteration (08) : ";

			std::cout << "enter \'b\' to break : "; char x = 0; std::cin >> x;
			
			if (x == 'b') 
			{
				break;
			}
		}
	}

//  ---------------------------------------------------------------------------------

	{
		while (1)
		{
			std::cout << "main : iteration (09) : ";

			std::cout << "enter \'b\' to break : "; char x = 0; std::cin >> x;
			
			if (x == 'b') 
			{
				break;
			}
		}
	}

//  ---------------------------------------------------------------------------------

	{
		char x = 0;

		while (x != 'b')
		{
			std::cout << "main : iteration (10) : ";

			std::cout << "enter \'b\' to break : "; std::cin >> x;
		}
	}

//  ---------------------------------------------------------------------------------

	{
		char x = 0;

		do
		{
			std::cout << "main : iteration (11) : ";

			std::cout << "enter \'b\' to break : "; std::cin >> x;
		} 
		while (x != 'b');
	}
}