#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>

int main()
{
	const auto object = new const auto(42); // good: initialized dynamic variable

	std::cout << *object << std::endl;

	delete object; // good: no dynamic variable memory leak

//  ================================================================================================

	const std::size_t size = 5;

	const auto array = new int[size]{}; // good: zero initialized dynamic array

	const auto middle = size / 2;

	array[middle] = 42;

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << array[i] << (i + 1 == size ? '\n' : ' ');
	}

	delete[] array; // good: no dynamic array memory leak, remember delete version

//  ================================================================================================

	const auto buffer = new int[size]; 

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

	delete[] buffer; // good: no memory leak

	return 0;
}