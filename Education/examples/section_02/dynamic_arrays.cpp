#include <iostream>

int main()
{
	auto ptr_int = new int(42); // good: initialized dynamic variable

	std::cout << *ptr_int << std::endl;

	delete ptr_int; // good: no dynamic variable memory leak

	const auto size = 10;

	auto ptr_array = new int[size] {}; // good: zero initialized dynamic array

	const auto m = size / 2;

	ptr_array[m] = 42;

	for (auto i = 0; i < size; ++i)
	{
		std::cout << ptr_array[i];

		std::cout << (i + 1 == size ? '\n' : ' ');
	}

	delete[] ptr_array; // good: no dynamic array memory leak

//	delete ptr_array; // bad: wrong delete

	std::cout << "Enter array size: ";

	int n{}; // note: runtime non-constant variable

	std::cin >> n;

	std::cout << "Enter " << n << " integer values: ";

	auto s = new int[n];

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
				std::swap(s[i], s[j]);
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