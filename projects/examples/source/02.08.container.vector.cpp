#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

int main()
{
	const std::size_t size = 5;

	std::vector < int > vector(size, 0);

	std::iota(std::begin(vector), std::end(vector), 1);

	std::ranges::reverse(vector);

//  ================================================================================================

	for (std::size_t i = 0; i < size - 1; ++i) // support: сортировка пузырьком
	{
		for (std::size_t j = i + 1; j < size; ++j)
		{
			if (vector[i] > vector[j]) std::swap(vector[i], vector[j]);
		}
	}

//  ================================================================================================

	for (const auto element : vector) std::cout << element << ' ';

	std::cout << std::endl;

	return 0;
}