#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <numeric>
#include <utility>
#include <vector>

//  ================================================================================================

void sort(std::vector < int > & vector, std::size_t left, std::size_t right)
{
	for (auto i = left + 1; i < right; ++i) 
	{
		for (auto j = i; j > left; --j)
		{
			if (vector[j - 1] > vector[j]) 
			{
				std::swap(vector[j], vector[j - 1]);
			}
		}
	}
}

//  ================================================================================================

void merge(std::vector < int > & vector, std::size_t left, std::size_t middle, std::size_t right)
{
	std::vector < int > copy(right - left, 0);

	for (auto i = left, j = middle, k = 0uz; k < std::size(copy); ++k) 
	{
		if (i < middle && ((j < right && vector[i] <= vector[j]) || j == right))
		{
			copy[k] = vector[i++];
		}
		else
		{
			copy[k] = vector[j++];
		}
	}

	for (auto i = 0uz, j = 0uz; j < std::size(copy); ++j) 
	{
		vector[left + i++] = copy[j];
	}
}

//  ================================================================================================

void split(std::vector < int > & vector, std::size_t left, std::size_t right)
{
	if (right - left <= 64)
	{
		sort(vector, left, right);
	}
	else
	{
		auto middle = std::midpoint(left, right); 
		
		split(vector, left, middle       );
		split(vector,       middle, right);
		merge(vector, left, middle, right);
	}
}

//  ================================================================================================

void timsort(std::vector < int > & vector, std::size_t left, std::size_t right)
{
	split(vector, left, right);
}

//  ================================================================================================

int main()
{
	auto size = 1'000uz;

	std::vector < int > vector(size, 0);

	for (auto i = 0uz; i < size; ++i)
	{
		vector[i] = size - i;
	}

	timsort(vector, 0, size);

	assert(std::ranges::is_sorted(vector));
}