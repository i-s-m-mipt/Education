/////////////////////////////////////////////////////////////////////////////////////////////////

// support : www.cs.usfca.edu/~galles/visualization/ComparisonSort.html

/////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////

void merge(std::vector < int > & vector, std::size_t left, std::size_t middle, std::size_t right)
{
	auto size = right - left;

	std::vector < int > buffer(size, 0);

	for (auto i = left, j = middle, k = 0uz; k < size; ++k) 
	{
		if (i < middle && ((j < right && vector[i] <= vector[j]) || j == right))
		{
			buffer[k] = vector[i++];
		}
		else
		{
			buffer[k] = vector[j++];
		}
	}

	for (auto i = 0uz, j = 0uz; j < size; ++j) 
	{
		vector[left + i++] = buffer[j];
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void split(std::vector < int > & vector, std::size_t left, std::size_t right)
{
	if (right - left > 64)
	{
		auto middle = std::midpoint(left, right);

	//  -----------------------------------------

		split(vector, left,   middle);
		
		split(vector, middle, right );

	//  -----------------------------------------

		merge(vector, left, middle, right);
	}
	else
	{
		sort (vector, left, right);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void sort(std::vector < int > & vector)
{
	split(vector, 0, std::size(vector));
}

/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto size = 1'000uz;

//  ---------------------------------------

	std::vector < int > vector(size, 0);

//  ---------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		vector[i] = size - i;
	}

//  ---------------------------------------

	sort(vector);

//  ---------------------------------------

	assert(std::ranges::is_sorted(vector));
}

/////////////////////////////////////////////////////////////////////////////////////////////////