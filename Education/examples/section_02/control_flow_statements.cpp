#include <iostream>

int main()
{
    std::cout << "Enter integer value: ";

    int x{}; // good: zero initialized variable for input

    std::cin >> x;

    if (auto y = x * 4 + 10; 42 == y) // good: 42 == y prevents error 42 = y
    {
        std::cout << "path 1\n";
    }
    else if (y > 0)
    {
        std::cout << "path 2\n";
    }
    else
    {
        if (x < 0)
        {
            std::cout << "path 3\n";
        }
        else
        { 
            std::cout << "path 4\n";
        }
    }

    std::cout << (x > 0 ? x : 42) << '\n'; // good: compact selection

    switch (auto y = x / 4 - 1; y)
    {
    [[likely]] case 0: // good: optimally generated machine code
    [[likely]] case 1:
    [[likely]] case 2:
    {
        std::cout << "path 1" << std::endl;
        [[fallthrough]]; // good: suppressed warning, clear intentions
    }
    case 3:
    {
        std::cout << "path 2" << std::endl;
        break;
    }
    [[unlikely]] case 4: // good: optimally generated machine code
    {
        std::cout << "path 3" << std::endl;
        break;
    }
    default: // good: secure code
    {
        std::cout << "path 4" << std::endl;
        break;
    }
    }

	const auto size = 5;

	for (auto i = 0; i < size; ++i) // note: clear counter
	{
		std::cout << "for 1: " << i << '\n';
	}

	for (auto i = 0, j = 0; i < size; ++i, j += 2) // good: useful comma separator syntax
	{
		std::cout << "for 2: " << i << ' ' << j << '\n';
	}

	//	for (auto i = 0; auto x = (i + 1) % size; ++i) {} // bad: declaration instead of condition

	for (auto i = size; i >= 0; --i)
	{
		if (i % 2 == 0)
		{
			continue;
		}

		std::cout << "for 4: " << i << '\n';
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

		std::cout << '\n';
	}

	for (auto i = 0; i < size; ++i)
	{
		for (auto j = 0; j < size; ++j)
		{
			for (auto k = 0; k < size; ++k)
			{
				std::cout << "for 6: " << i << ' ' << j << ' ' << k << '\n';

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
	} 
	while (c != 'n');

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