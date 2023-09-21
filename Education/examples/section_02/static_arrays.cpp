#include <iostream>

int main()
{
	const auto size = 10; // note: compile-time constant variable

	int a[size]{}; // good: zero initialized array

	int b[size]{ 1, 2, 3 }; // note: elements: { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0 }

	int c[]{ 1, 2, 3 }; // note: elements: { 1, 2, 3 }, size deduction -> 3

	*a = 42; // note: array name is a pointer to the first element

	const auto m = size / 2;

	*(a + m) = 42; // note: pointer arithmetic

	std::cout << a[m] << '\n'; // good: standard index access operator syntax

//	std::cout << *(&a[0] + m) << '\n'; // bad: redundant syntax

	std::cout << *(a + m) << '\n';
	std::cout << *(m + a) << '\n';

//	std::cout << m[a] << '\n'; // bad: inconvenient index access operator syntax

	std::cout << (a + m + 1) - (a + m - 1) << '\n'; // note: distance between elements

	for (int * p = a; p != (a + size); ++p)
	{
		std::cout << *p;

		std::cout << (p + 1 == a + size ? '\n' : ' '); // good: compact formatting
	}

	std::cout << "Enter array size: ";

	int n{};

	std::cin >> n;

	std::cout << "Enter " << n << " integer values: ";

	const auto buffer_size = 1024; // note: enough size

	int s[buffer_size]{};

	for (auto i = 0; i < n; ++i)
	{
		std::cin >> s[i];
	}

	for (auto i = 0; i < n - 1; ++i) // note: bubble sort
	{
		for (auto j = i + 1; j < n; ++j)
		{
			if (s[i] > s[j])
			{
				auto tmp = s[i]; s[i] = s[j]; s[j] = tmp;
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