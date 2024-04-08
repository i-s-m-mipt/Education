#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

int main()
{
	const std::size_t n = 5;

	std::vector < int > vector(n, 0); // note: create vector of n zero elements

	std::iota(std::begin(vector), std::end(vector), 1); // note: generate range 1, 2, 3, ...

	std::ranges::reverse(vector); // note: reverse range

	for (std::size_t i = 0; i < n - 1; ++i)
	{
		for (std::size_t j = i + 1; j < n; ++j)
		{
			if (vector[i] > vector[j]) // note: sort in ascending order
			{
				std::swap(vector[i], vector[j]);
			}
		}
	}

	for (const auto element : vector) std::cout << element << ' ';

	std::cout << std::endl;

	return 0;
}