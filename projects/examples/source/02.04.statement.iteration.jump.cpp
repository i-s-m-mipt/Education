#include <iostream>

int main()
{
	const std::size_t size = 5;

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << "for 1: " << i << std::endl;
	}

	for (std::size_t i = 0, j = 0; i < size; ++i, j += 2)
	{
		std::cout << "for 2: " << i << ' ' << j << std::endl;
	}

	for (std::size_t i = 0; [[maybe_unused]] auto x = (i + 1) % size; ++i) 
	{
		std::cout << "for 3: " << i << std::endl;
	}

//	for (std::size_t i = size; i >= 0; --i); // error

//  ================================================================================================

	for (std::size_t i = size; i >= 1; --i)
	{
		if (i % 2 == 0) continue;

		std::cout << "for 4: " << i << std::endl;
	}

//  ================================================================================================

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << "for 5: ";

		for (std::size_t j = 0; j < size; ++j)
		{
			if (j > i) break;

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

				if (i == 1 && j == 1 && k == 1) goto exit;
			}
		}
	}

exit:

//  ================================================================================================

	char c{};

	while (c != 'n')
	{
		std::cout << "Continue while? (y/n) "; std::cin >> c;
	}

//  ================================================================================================

	do
	{
		std::cout << "Continue do while? (y/n) "; std::cin >> c;
	} 
	while (c != 'n');

//  ================================================================================================

	for (;;)
	{
		std::cout << "Continue infinite for? (y/n) ";

		if (std::cin >> c; c == 'n') break;
	}

//  ================================================================================================

	while (true)
	{
		std::cout << "Continue infinite while? (y/n) ";

		if (std::cin >> c; c == 'n') break;
	}

	return 0;
}