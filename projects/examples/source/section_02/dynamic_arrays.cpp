#include <iostream>
#include <utility>

int main()
{
	auto ptr_int = new int(42); // good: initialized dynamic variable

	std::cout << *ptr_int << std::endl;

	delete ptr_int; // good: no dynamic variable memory leak

	std::size_t size = 10;

	auto ptr_array = new int[size]{}; // good: zero initialized dynamic array

	const auto m = size / 2;

	ptr_array[m] = 42;

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << ptr_array[i] << (i + 1 == size ? '\n' : ' ');
	}

	delete[] ptr_array; // good: no dynamic array memory leak

//	delete ptr_array; // bad: wrong delete

	std::cout << "Enter array size: "; std::size_t n{}; std::cin >> n;

	std::cout << "Enter " << n << " integer values: ";

	auto s = new int[n]; // note: non-constant size

	for (std::size_t i = 0; i < n; ++i)
	{
		std::cin >> s[i];
	}

	for (std::size_t i = 0; i < n - 1; ++i) // note: bubble sort
	{
		for (std::size_t j = i + 1; j < n; ++j)
		{
			if (s[i] > s[j])
			{
				std::swap(s[i], s[j]);
			}
		}
	}

	for (std::size_t i = 0; i < n; ++i)
	{
		std::cout << s[i] << (i + 1 == n ? '\n' : ' ');
	}

	delete[] s;

	return 0;
}