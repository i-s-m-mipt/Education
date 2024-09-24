#include <iostream>

int main()
{
	const std::size_t size = 5;

	for (std::size_t i = 0; i < size; ++i) // support: compiler-explorer.com
	{
		std::cout << "Iteration v01 : " << i << std::endl;
	}

	for (std::size_t i = 0, j = 0; i < size; ++i, j += 2)
	{
		std::cout << "Iteration v02 : " << i << std::endl;
	}

	for (std::size_t i = 0; [[maybe_unused]] auto x = (i < size); ++i) 
	{
		std::cout << "Iteration v03 : " << i << std::endl;
	}

//	for (std::size_t i = size; i >= 0; --i); // error
//	{
//		std::cout << "Iteration v04 : " << i << std::endl;
//	}

//  ================================================================================================

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << "Iteration v05 : " << i << std::endl;
		
		continue; // support: compiler-explorer.com

		std::cout << "Iteration v05 : " << i << std::endl;
	}

//  ================================================================================================

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << "Iteration v06 : ";

		std::cout << "Break? (y/n) "; char c{}; std::cin >> c; 
		
		if (c == 'y') break; // support: compiler-explorer.com
	}

//  ================================================================================================

	for (std::size_t i = 0; i < size; ++i)
	{
		for (std::size_t j = 0; j < size; ++j)
		{
			for (std::size_t k = 0; k < size; ++k)
			{
				std::cout << "Iteration v07 : ";

				std::cout << "Break? (y/n) "; char c{}; std::cin >> c; 
		
				if (c == 'y') goto exit; // support: compiler-explorer.com
			}
		}
	}

exit:

//  ================================================================================================

	for (;;)
	{
		std::cout << "Iteration v08 : ";

		std::cout << "Break? (y/n) "; char c{}; std::cin >> c; 
		
		if (c == 'y') break;
	}

//  ================================================================================================

	while (true)
	{
		std::cout << "Iteration v09 : ";

		std::cout << "Break? (y/n) "; char c{}; std::cin >> c; 
		
		if (c == 'y') break;
	}

//  ================================================================================================

	char c1{};

	while (c1 != 'y')
	{
		std::cout << "Iteration v10 : ";

		std::cout << "Break? (y/n) "; std::cin >> c1;
	}

//  ================================================================================================

	char c2{};

	do
	{
		std::cout << "Iteration v11 : ";

		std::cout << "Break? (y/n) "; std::cin >> c2;
	} 
	while (c2 != 'y');

	return 0;
}