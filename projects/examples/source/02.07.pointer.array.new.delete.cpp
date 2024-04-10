#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>

int main()
{
	const int * const ptr_int = new int(42); // good: initialized dynamic variable

	std::cout << *ptr_int << std::endl;

	delete ptr_int; // good: no dynamic variable memory leak

	const std::size_t size = 10;

	const auto ptr_array = new int[size]{}; // good: zero initialized dynamic array

	const auto m = size / 2;

	ptr_array[m] = 42;

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << ptr_array[i] << (i + 1 == size ? '\n' : ' ');
	}

	delete[] ptr_array; // good: no dynamic array memory leak

//	delete ptr_array; // bad: wrong delete

	std::size_t n = 5; // note: non-constant size as runtime variable

	const auto s = new int[n]; 

	std::iota(s, s + n, 1); // note: generate range 1, 2, 3, ...

	std::ranges::reverse(s, s + n); // note: reverse range

	for (std::size_t i = 0; i < n - 1; ++i) // note: bubble sort
	{
		for (std::size_t j = i + 1; j < n; ++j)
		{
			if (s[i] > s[j]) // note: sort in ascending order
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