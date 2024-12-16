#include <iostream>

int main()
{
	auto size = 5uz;

//  ------------------------------------------------------------------------------------------------

	for (auto i = 0uz; i < size; ++i) // support: compiler-explorer.com
	{
		std::cout << "iteration (01) : i = " << i << '\n';
	}

//  ------------------------------------------------------------------------------------------------

	for (auto i = 0uz, j = 0uz; i < size; ++i, j += 2)
	{
		std::cout << "iteration (02) : i = " << i << '\n';
	}

//  ------------------------------------------------------------------------------------------------

	for (auto i = 0uz; [[maybe_unused]] auto x = i < size; ++i) 
	{
		std::cout << "iteration (03) : i = " << i << '\n';
	}

//  ------------------------------------------------------------------------------------------------

//	for (auto i = size; i >= 0; --i); // error
//	{
//		std::cout << "iteration (04) : i = " << i << '\n';
//	}

//  ------------------------------------------------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		std::cout << "iteration (05) : i = " << i << '\n';
		
		continue; // support: compiler-explorer.com

		std::cout << "iteration (05) : i = " << i << '\n';
	}

//  ------------------------------------------------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		std::cout << "iteration (06) : ";

		std::cout << "Break? (y/n) "; char c; std::cin >> c; 
		
		if (c == 'y') 
		{
			break; // support: compiler-explorer.com
		}
	}

//  ------------------------------------------------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			for (auto k = 0uz; k < size; ++k)
			{
				std::cout << "iteration (07) : ";

				std::cout << "Break? (y/n) "; char c; std::cin >> c; 
		
				if (c == 'y') 
				{
					goto exit; // support: compiler-explorer.com
				}
			}
		}
	}

exit:

//  ------------------------------------------------------------------------------------------------

	for (;;)
	{
		std::cout << "iteration (08) : ";

		std::cout << "Break? (y/n) "; char c; std::cin >> c; 
		
		if (c == 'y') 
		{
			break;
		}
	}

//  ------------------------------------------------------------------------------------------------

	while (true)
	{
		std::cout << "iteration (09) : ";

		std::cout << "Break? (y/n) "; char c; std::cin >> c; 
		
		if (c == 'y') 
		{
			break;
		}
	}

//  ------------------------------------------------------------------------------------------------

	char c1 = 'n';

	while (c1 != 'y')
	{
		std::cout << "iteration (10) : ";

		std::cout << "Break? (y/n) "; std::cin >> c1;
	}

//  ------------------------------------------------------------------------------------------------

	char c2 = 'n';

	do
	{
		std::cout << "iteration (11) : ";

		std::cout << "Break? (y/n) "; std::cin >> c2;
	} 
	while (c2 != 'y');
}