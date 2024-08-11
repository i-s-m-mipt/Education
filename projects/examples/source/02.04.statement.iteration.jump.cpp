#include <iostream>

int main()
{
	const std::size_t size = 5;

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << "Loop for (1): " << i << std::endl;
	}

	for (std::size_t i = 0, j = 0; i < size; ++i, j += 2)
	{
		std::cout << "Loop for (2): " << i << ' ' << j << std::endl;
	}

	for (std::size_t i = 0; [[maybe_unused]] auto x = (i + 1) % size; ++i) 
	{
		std::cout << "Loop for (3): " << i << std::endl;
	}

//	for (std::size_t i = size; i >= 0; --i); // error

//  ================================================================================================

	for (std::size_t i = size; i >= 1; --i)
	{
		if (i % 2 == 0) continue;

		std::cout << "Loop for (4): " << i << std::endl;
	}

//  ================================================================================================

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << "Loop for (5): ";

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
				std::cout << "Loop for (6): " << i << ' ' << j << ' ' << k << std::endl;

				if (i == 1 && j == 1 && k == 1) goto exit;
			}
		}
	}

exit:

//  ================================================================================================

	char c1{};

	while (c1 != 'n')
	{
		std::cout << "Continue loop? (y/n) "; std::cin >> c1;
	}

//  ================================================================================================

	char c2{};

	do
	{
		std::cout << "Continue loop? (y/n) "; std::cin >> c2;
	} 
	while (c2 != 'n');

//  ================================================================================================

	for (;;)
	{
		std::cout << "Continue loop? (y/n) "; char c{}; std::cin >> c;

		if (c == 'n') break;
	}

//  ================================================================================================

	while (true)
	{
		std::cout << "Continue loop? (y/n) "; char c{}; std::cin >> c;

		if (c == 'n') break;
	}

	return 0;
}