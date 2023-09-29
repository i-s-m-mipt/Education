#include <iostream>

int main()
{
	const auto size = 5;

	for (auto i = 0; i < size; ++i) // note: clear counter
	{
		std::cout << "for 1: " << i << std::endl;
	}

	for (auto i = 0, j = 0; i < size; ++i, j += 2) // good: useful comma separator syntax
	{
		std::cout << "for 2: " << i << ' ' << j << std::endl;
	}

	//	for (auto i = 0; auto x = (i + 1) % size; ++i) {} // bad: declaration instead of condition

	for (auto i = size; i >= 0; --i)
	{
		if (i % 2 == 0)
		{
			continue;
		}

		std::cout << "for 4: " << i << std::endl;
	}

	for (auto i = 0; i < size; ++i)
	{
		std::cout << "for 5: ";

		for (auto j = 0; j < size; ++j)
		{
			if (j > i)
			{
				break;
			}

			std::cout << j << ' ';
		}

		std::cout << std::endl;
	}

	for (auto i = 0; i < size; ++i)
	{
		for (auto j = 0; j < size; ++j)
		{
			for (auto k = 0; k < size; ++k)
			{
				std::cout << "for 6: " << i << ' ' << j << ' ' << k << std::endl;

				if (auto stop = size / 2; i == stop && j == stop && k == stop)
				{
					goto exit; // note: use goto only to exit nested loops
				}
			}
		}
	}

exit:

	char c{};

	while (c != 'n') // note: undefined counter
	{
		std::cout << "Continue (y/n) ? ";

		std::cin >> c;
	}

	do
	{
		std::cout << "Continue (y/n) ? ";

		std::cin >> c;
	} while (c != 'n');

	for (;;) // note: unusual infinite loop
	{
		std::cout << "Continue (y/n) ? ";

		std::cin >> c;

		if (c == 'n')
		{
			break;
		}
	}

	while (true)
	{
		std::cout << "Continue (y/n) ? ";

		std::cin >> c;

		if (c == 'n')
		{
			break;
		}
	}

	return 0;
}