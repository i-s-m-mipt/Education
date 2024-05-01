#include <iostream>

int main()
{
	const std::size_t size = 5;

	for (std::size_t i = 0; i < size; ++i) // note: clear counter
	{
		std::cout << "for 1: " << i << std::endl;
	}

	for (std::size_t i = 0, j = 0; i < size; ++i, j += 2) // good: useful comma separator syntax
	{
		std::cout << "for 2: " << i << ' ' << j << std::endl;
	}

//	for (std::size_t i = 0; auto x = (i + 1) % size; ++i) {} // bad: declaration instead of condition

//	for (std::size_t i = size; i >= 0; --i); // error: infinite loop, two's complement

//  ================================================================================================

	for (std::size_t i = size; i >= 1; --i)
	{
		if (i % 2 == 0)
		{
			continue;
		}

		std::cout << "for 4: " << i << std::endl;
	}

//  ================================================================================================

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << "for 5: ";

		for (std::size_t j = 0; j < size; ++j)
		{
			if (j > i)
			{
				break;
			}

			std::cout << j << ' ';
		}

		std::cout << std::endl;
	}

//  ================================================================================================

	for (std::size_t i = 0; i < size; ++i)
	{
		for (std::size_t j = 0; j < size; ++j)
		{
			for (std::size_t k = 0; k < size; ++k)
			{
				std::cout << "for 6: " << i << ' ' << j << ' ' << k << std::endl;

				if (i == 1 && j == 1 && k == 1)
				{
					goto exit; // note: use goto only to exit nested loops
				}
			}
		}
	}

exit:

//  ================================================================================================

	char c{};

	while (c != 'n') // note: undefined counter
	{
		std::cout << "Continue while? (y/n) "; std::cin >> c;
	}

	do
	{
		std::cout << "Continue do while? (y/n) "; std::cin >> c;
	} 
	while (c != 'n');

//  ================================================================================================

	for (;;) // note: unusual infinite loop
	{
		std::cout << "Continue infinite for? (y/n) ";

		if (std::cin >> c; c == 'n') break;
	}

	while (true)
	{
		std::cout << "Continue infinite while? (y/n) ";

		if (std::cin >> c; c == 'n') break;
	}

	return 0;
}