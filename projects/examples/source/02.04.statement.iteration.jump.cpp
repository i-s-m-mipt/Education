#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto size = 5uz;

//  ---------------------------------------------------------------------------------------------

	for (auto i = 0uz; i < size; ++i) // support: compiler-explorer.com
	{
		std::cout << "main : iteration (01) : i = " << i << '\n';
	}

//  ---------------------------------------------------------------------------------------------

	for (auto i = 0uz, j = 0uz; i < size; ++i, j += 2)
	{
		std::cout << "main : iteration (02) : i = " << i << " j = " << j << '\n';
	}

//  ---------------------------------------------------------------------------------------------

	for (auto i = 0uz; [[maybe_unused]] auto j = i < size; ++i) 
	{
		std::cout << "main : iteration (03) : i = " << i << '\n';
	}

//  ---------------------------------------------------------------------------------------------

//	for (auto i = size; i >= 0; --i); // error
//	{
//		std::cout << "main : iteration (04) : i = " << i << '\n';
//	}

//  ---------------------------------------------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		std::cout << "main : iteration (05) : i = " << i << '\n';
		
		continue; // support: compiler-explorer.com

		std::cout << "main : iteration (05) : i = " << i << '\n';
	}

//  ---------------------------------------------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		std::cout << "main : iteration (06) : i = " << i << ' ';

		std::cout << "break? (y/n) "; char c; std::cin >> c; 
		
		if (c == 'y') 
		{
			break; // support: compiler-explorer.com
		}
	}

//  ---------------------------------------------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			for (auto k = 0uz; k < size; ++k)
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

//  ---------------------------------------------------------------------------------------------

	for (;;)
	{
		std::cout << "main : iteration (08) : ";

		std::cout << "break? (y/n) "; char c; std::cin >> c; 
		
		if (c == 'y') 
		{
			break;
		}
	}

//  ---------------------------------------------------------------------------------------------

	while (true)
	{
		std::cout << "main : iteration (09) : ";

		std::cout << "break? (y/n) "; char c; std::cin >> c; 
		
		if (c == 'y') 
		{
			break;
		}
	}

//  ---------------------------------------------------------------------------------------------

	char c1 = 'n';

	while (c1 != 'y')
	{
		std::cout << "main : iteration (10) : ";

		std::cout << "break? (y/n) "; std::cin >> c1;
	}

//  ---------------------------------------------------------------------------------------------

	char c2 = 'n';

	do
	{
		std::cout << "main : iteration (11) : ";

		std::cout << "break? (y/n) "; std::cin >> c2;
	} 
	while (c2 != 'y');
}