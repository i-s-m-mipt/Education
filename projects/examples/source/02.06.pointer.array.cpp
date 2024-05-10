#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>

int main()
{
	const std::size_t size = 5;

	[[maybe_unused]]       int array_1[size]{         }; // elements: { 0, 0, 0, 0, 0 }
	[[maybe_unused]] const int array_2[size]{ 1, 2, 3 }; // elements: { 1, 2, 3, 0, 0 }
	[[maybe_unused]] const int array_3[    ]{ 1, 2, 3 }; // elements: { 1, 2, 3       }
	
//	[[maybe_unused]] const int array_4[1'000'000'000]{}; // error

//  ================================================================================================

//	std::cout << sizeof(array_1) / sizeof(array_1[0]) << std::endl; // bad

	std::cout << std::size(array_1) << std::endl; // output: 5

//  ================================================================================================

	*array_1 = 42;

	const auto middle = size / 2;

	*(array_1 + middle) = 42;

//	*(array_1 + 10'000) = 42; // bad

	std::cout << array_1[middle] << std::endl; // output: 42

//	std::cout << *(&array_1[0] + middle) << std::endl; // bad

//	std::cout << middle[array_1] << std::endl; // bad

	std::cout << (array_1 + middle + 1) - (array_1 + middle - 1) << std::endl; // output: 2

//	[[maybe_unused]] auto delta = array_2 - array_1; // bad

	for (const int * ptr = array_1; ptr != (array_1 + size); ++ptr)
	{
		std::cout << *ptr << (ptr + 1 == array_1 + size ? '\n' : ' '); // output: 42 0 42 0 0
	}

//  ================================================================================================

	const std::size_t buffer_size = 1024;

	int buffer[buffer_size]{};

	std::iota(buffer, buffer + size, 1);

	std::ranges::reverse(buffer, buffer + size);

//  ================================================================================================

	for (std::size_t i = 0; i < size - 1; ++i)
	{
		for (std::size_t j = i + 1; j < size; ++j)
		{
			if (buffer[i] > buffer[j]) std::swap(buffer[i], buffer[j]);
		}
	}

//  ================================================================================================

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << buffer[i] << (i + 1 == size ? '\n' : ' '); // output: 1 2 3 4 5
	}

	return 0;
}