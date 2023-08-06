#include <iostream>

int main()
{
	const std::size_t size = 1024;

	int a[size]{};
	int b[size]{1, 2, 3};
	int c[]{1, 2, 3};

	std::size_t n;

	std::cin >> n;

	if (n <= size)
	{
		for (std::size_t i = 0; i < n; ++i)
		{
			std::cin >> a[i];
		}

		for (std::size_t i = 0; i < n - 1; ++i)
		{
			for (std::size_t j = i + 1; j < n; ++j)
			{
				if (a[i] > a[j])
				{
					std::swap(a[i], a[j]);
				}
			}
		}

		for (std::size_t i = 0; i < n; ++i)
		{
			std::cout << a[i] << ' ';
		}
	}

	return 0;
}