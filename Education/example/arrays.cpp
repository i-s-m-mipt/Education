#include <iostream>

int main()
{
	const auto size = 10;

	int a[size]{};
	int b[size]{ 1, 2, 3 };
	int c[]    { 1, 2, 3 };

	*a = 42;

	const auto m = size / 2;

	*(a + m) = 42;

	std::cout <<    a[m]      << '\n';
	std::cout << *(&a[0] + m) << '\n';
	std::cout << *( a    + m) << '\n';
	std::cout << *( m +    a) << '\n';
	std::cout <<    m[a]      << '\n';

	std::cout << (a + m + 1) - (a + m - 1) << '\n';

	for (int * p = a; p != (a + size); ++p)
	{
		std::cout << *p;

		std::cout << (p + 1 == a + size ? '\n' : ' ');
	}

	auto ptr_int = new int(42);

	std::cout << *ptr_int << '\n';

	delete ptr_int;

	auto ptr_array = new int[size]{};

	ptr_array[m] = 42;

	for (auto i = 0; i < size; ++i)
	{
		std::cout << ptr_array[i];

		std::cout << (i + 1 == size ? '\n' : ' ');
	}

	delete[] ptr_array;

	int n{};

	std::cin >> n;

	auto s = new int[n];

	for (auto i = 0; i < n; ++i)
	{
		std::cin >> s[i];
	}

	for (auto i = 0; i < n - 1; ++i)
	{
		for (auto j = i + 1; j < n; ++j)
		{
			if (s[i] > s[j])
			{
				auto tmp = s[i]; 
				s[i] = s[j];
				s[j] = tmp;
			}
		}
	}

	for (auto i = 0; i < n; ++i)
	{
		std::cout << s[i];

		std::cout << (i + 1 == size ? '\n' : ' ');
	}

	delete[] s;

	return 0;
}