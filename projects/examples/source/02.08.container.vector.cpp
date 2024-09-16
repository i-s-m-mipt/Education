#include <cassert>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

int main()
{
	const std::size_t size = 5;

	std::vector < int > vector(size, 0);

	std::iota(std::begin(vector), std::end(vector), 1);

	for (std::size_t i = 0; i < size - 1; ++i)
	{
		for (std::size_t j = i + 1; j < size; ++j)
		{
			if (vector[i] < vector[j]) 
			{
				std::swap(vector[i], vector[j]);
			}
		}
	}

	assert(vector == std::vector < int > ({ 5, 4, 3, 2, 1 }));

	return 0;
}