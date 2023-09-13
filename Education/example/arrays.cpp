#include <iostream>

int main()
{
	const auto size = 10; // attention: compile-time constant variable

	int a[size]{}; // good: zero initialized array

	int b[size]{ 1, 2, 3 }; // attention: elements: { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0 }

	int c[]{ 1, 2, 3 }; // attention: elements: { 1, 2, 3 }, size = 3 deduction

	*a = 42; // attention: array name is a pointer to the first element

	const auto m = size / 2;

	*(a + m) = 42; // attention: pointer arithmetic

	std::cout << a[m] << '\n'; // good: standard syntax

//	std::cout << *(&a[0] + m) << '\n'; // bad: redundant syntax

	std::cout << *(a + m) << '\n';
	std::cout << *(m + a) << '\n';

//	std::cout << m[a] << '\n'; // bad: irregular syntax

	std::cout << (a + m + 1) - (a + m - 1) << '\n'; // attention: distance between elements

	for (int * p = a; p != (a + size); ++p)
	{
		std::cout << *p;

		std::cout << (p + 1 == a + size ? '\n' : ' '); // attention: formatting
	}

	auto ptr_int = new int(42); // good: initialized dynamic variable

	std::cout << *ptr_int << '\n';

	delete ptr_int; // attention: freeing dynamic variable memory

	auto ptr_array = new int[size]{}; // good: zero initialized dynamic array

	ptr_array[m] = 42;

	for (auto i = 0; i < size; ++i)
	{
		std::cout << ptr_array[i];

		std::cout << (i + 1 == size ? '\n' : ' ');
	}

	delete[] ptr_array; // attention: freeing dynamic array memory

	int n{}; // attention: runtime non-constant variable

	std::cin >> n;

	auto s = new int[n];

	for (auto i = 0; i < n; ++i)
	{
		std::cin >> s[i];
	}

	for (auto i = 0; i < n - 1; ++i) // attention: bubble sort
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