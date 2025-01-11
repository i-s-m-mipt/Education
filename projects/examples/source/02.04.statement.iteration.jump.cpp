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

//  =================================================================================

	{
		for (auto i = 0uz, j = 0uz; i < 5; ++i, j += 2)
		{
			std::cout << "main : iteration (02) : i = " << i << " j = " << j << '\n';
		}
	}

//  =================================================================================	

	{
		for (auto i = 0uz; [[maybe_unused]] auto j = i < 5; ++i) 
		{
			std::cout << "main : iteration (03) : i = " << i << '\n';
		}
	}
	

//  =================================================================================

	{
//		for (auto i = 5uz; i >= 0; --i); // error
//		{
//			std::cout << "main : iteration (04) : i = " << i << '\n';
//		}
	}

//  =================================================================================

	{
		for (auto i = 0uz; i < 5; ++i)
		{
			std::cout << "main : iteration (05) : i = " << i << '\n';
			
			continue; // support: compiler-explorer.com

			std::cout << "main : iteration (05) : i = " << i << '\n';
		}
	}
	
//  =================================================================================

	{
		for (auto i = 0uz; i < 5; ++i)
		{
			std::cout << "main : iteration (06) : i = " << i << ' ';

			std::cout << "break? (y/n) "; char c; std::cin >> c; 
			
			if (c == 'y') 
			{
				break; // support: compiler-explorer.com
			}
		}
	}
	
//  =================================================================================

	{
		for (auto i = 0uz; i < 5; ++i)
		{
			for (auto j = 0uz; j < 5; ++j)
			{
				for (auto k = 0uz; k < 5; ++k)
				{
					std::cout << "main : iteration (07) : ";
					
					std::cout << "i = " << i << " j = " << j << " k = " << k << ' ';

					std::cout << "break? (y/n) "; char c; std::cin >> c; 
			
					if (c == 'y') 
					{
						goto exit; // support: compiler-explorer.com
					}
				}
			}
		}

		exit:
	}
	
//  =================================================================================

	{
		for (;;)
		{
			std::cout << "main : iteration (08) : ";

			std::cout << "break? (y/n) "; char c; std::cin >> c; 
			
			if (c == 'y') 
			{
				break;
			}
		}
	}

//  =================================================================================

	{
		while (true)
		{
			std::cout << "main : iteration (09) : ";

			std::cout << "break? (y/n) "; char c; std::cin >> c; 
			
			if (c == 'y') 
			{
				break;
			}
		}
	}

//  =================================================================================

	{
		auto c = 'n';

		while (c != 'y')
		{
			std::cout << "main : iteration (10) : ";

			std::cout << "break? (y/n) "; std::cin >> c;
		}
	}

//  =================================================================================

	{
		auto c = 'n';

		do
		{
			std::cout << "main : iteration (11) : ";

			std::cout << "break? (y/n) "; std::cin >> c;
		} 
		while (c != 'y');
	}
}