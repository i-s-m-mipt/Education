#include <iostream>

int main()
{
	for (auto i = 0ull; i < 100; ++i)
	{
		if (i % 2 == 0)
		{
			continue;
		}

		// ...
	}

	for (std::size_t i = 0, j = 100; i <= j; i += 3, --j)
	{
		for (std::size_t k = 0; k < 10; ++k)
		{
			if (k * 10 < i)
			{
				break;
			}
		}

		// ...
	}

	for (std::size_t i = 0; i < 10; ++i)
	{
		for (std::size_t j = 0; j < 10; ++j)
		{
			for (std::size_t k = 0; k < 10; ++k)
			{
				if (i == 5 && j == 5 && k == 5)
				{
					goto exit;
				}

				// ...
			}
		}
	}

	exit:

	for(;;)
	{
		// ...
	}

	while (true)
	{
		// ...
	}

	auto x = 0;

	while (std::cin >> x)
	{
		std::cout << x << std::endl;
	}

	do
	{
		std::cin >> x;
	} 
	while (x != 42);

	system("pause");

	return 0;
}