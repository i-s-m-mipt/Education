#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>

int main()
{
	const std::size_t size = 5;

	int array_1[size]{}; // good: zero initialized array

	[[maybe_unused]] const int array_2[size]{ 1, 2, 3 }; // note: elements: { 1, 2, 3, 0, 0 }
	[[maybe_unused]] const int array_3[    ]{ 1, 2, 3 }; // note: elements: { 1, 2, 3 }, size deduction -> 3

//	const int array_4[2]{ 1, 2, 3 }; // error: too many initializers

//	const int array_5[1'000'000'000]{}; // bad: array is too large, use dynamic array

//  ================================================================================================

	std::cout << sizeof(array_1) / sizeof(array_1[0]) << std::endl; // note: old style approach

	std::cout << std::size(array_1) << std::endl; // good: function for static arrays and containers

//  ================================================================================================

	*array_1 = 42; // note: array name is a pointer to the first element

	const auto middle = size / 2;

	*(array_1 + middle) = 42; // note: pointer arithmetic

//	*(array_1 + 100000) = 42; // bad: undefined behavior, page fault / segmentation fault

//	std::cout << *(&array_1[0] + middle) << std::endl; // bad: redundant syntax

	std::cout << array_1[middle] << std::endl; // good: standard index access operator syntax

//	std::cout << middle[array_1] << std::endl; // bad: inconvenient index access operator syntax

	std::cout << (array_1 + middle + 1) - 
				 (array_1 + middle - 1) << std::endl; // note: distance between elements

//	auto delta = array_2 - array_1; // bad: pointers to different arrays

	for (const int * ptr = array_1; ptr != (array_1 + size); ++ptr)
	{
		std::cout << *ptr << (ptr + 1 == array_1 + size ? '\n' : ' ');
	}

//  ================================================================================================

	const std::size_t buffer_size = 1024;

	int buffer[buffer_size]{}; // note: buffer_size >= size

	std::iota(buffer, buffer + size, 1); // note: generate range 1, 2, 3, ...

	std::ranges::reverse(buffer, buffer + size); // note: reverse range

//  ================================================================================================

	for (std::size_t i = 0; i < size - 1; ++i) // note: bubble sort
	{
		for (std::size_t j = i + 1; j < size; ++j)
		{
			if (buffer[i] > buffer[j]) // note: sort in ascending order
			{
				std::swap(buffer[i], buffer[j]);
			}
		}
	}

//  ================================================================================================

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << buffer[i] << (i + 1 == size ? '\n' : ' ');
	}

	return 0;
}