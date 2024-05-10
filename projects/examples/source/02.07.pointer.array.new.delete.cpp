#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>

int main()
{
	const auto object = new const auto(42);

	std::cout << *object << std::endl; // output: 42

	delete object;

//  ================================================================================================

	const std::size_t size = 5;

	const auto array = new int[size]{};

	const auto middle = size / 2;

	array[middle] = 42;

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << array[i] << (i + 1 == size ? '\n' : ' '); // output: 0 0 42 0 0
	}

//	delete   array; // warning

	delete[] array;

//  ================================================================================================

	const auto buffer = new int[size]; 

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

	delete[] buffer;

	return 0;
}