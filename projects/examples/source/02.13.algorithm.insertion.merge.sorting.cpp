#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

//  ================================================================================================

void insertion_sort(std::vector < int > & vector, std::size_t l, std::size_t r) 
{
	for (auto i = l + 1; i < r; ++i) 
	{
		for (auto j = i; j > l; --j)
		{
			if (vector[j - 1] > vector[j]) std::swap(vector[j], vector[j - 1]);
		}
	}
}

//  ================================================================================================

void merge_sort(std::vector < int > & vector, std::size_t l, std::size_t m, std::size_t r)
{
	const auto begin = l, end = m;

	std::vector < int > copy(r - l, 0);

	for (auto & element : copy) 
	{
		element = vector[(l < end && ((m < r && vector[l] <= vector[m]) || (m == r))) ? l++ : m++];
	}

	for (std::size_t i = 0; auto element : copy) vector[begin + (i++)] = element;
}

//  ================================================================================================

void merge_sort(std::vector < int > & vector, std::size_t l, std::size_t r) 
{
	if (static const std::size_t block = 64; r - l <= block)
	{
		insertion_sort(vector, l, r); // note: сложность O(N^2)
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
	const std::size_t size = 1'000;

	std::vector < int > vector(size, 0);

	std::iota(std::begin(vector), std::end(vector), 1);

	std::ranges::reverse(vector);

	merge_sort(vector, 0, size); // note: сложность O(N*log(N)) амортизированная

	for (const auto element : vector) std::cout << element << ' ';

	std::cout << std::endl;

	return 0;
}