#include <algorithm>
#include <cassert>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

//  ================================================================================================

void block_sort(std::vector < int > & vector, std::size_t l, std::size_t r)
{
	for (auto i = l + 1; i < r; ++i) 
	{
		for (auto j = i; j > l; --j)
		{
			if (vector[j - 1] < vector[j]) 
			{
				std::swap(vector[j], vector[j - 1]);
			}
		}
	}
}

//  ================================================================================================

void merge_sort(std::vector < int > & vector, std::size_t l, std::size_t m, std::size_t r)
{
	std::vector < int > copy(r - l, 0);

	for (auto i = l, j = m; auto & element : copy) 
	{
		if (i < m && ((j < r && vector[i] >= vector[j]) || (j == r)))
		{
			element = vector[i++];
		}
		else
		{
			element = vector[j++];
		}
	}

	for (std::size_t i = 0; auto element : copy) vector[l + i++] = element;
}

//  ================================================================================================

void merge_sort(std::vector < int > & vector, std::size_t l, std::size_t r)
{
	if (static const std::size_t block = 64; r - l <= block)
	{
		block_sort(vector, l, r);
	}
	else
	{
		const auto m = std::midpoint(l, r); 
		
		merge_sort(vector, l, m   );
		merge_sort(vector,    m, r);
		merge_sort(vector, l, m, r);
	}
}

//  ================================================================================================

int main()
{
	const std::size_t size = 1000;

	std::vector < int > vector(size, 0);

	std::ranges::iota(vector, 1);

	merge_sort(vector, 0, size);

	assert(std::ranges::is_sorted(vector, std::ranges::greater()));

	return 0;
}