#include <iostream>

int main()
{
	std::size_t n;

	std::cin >> n;

	auto a = new int[n];

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

	delete[] a;

	system("pause");

	return 0;
}