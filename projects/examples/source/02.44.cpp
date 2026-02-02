////////////////////////////////////////////////////////////////////////////////////

// chapter : Basics of Programming

////////////////////////////////////////////////////////////////////////////////////

// section : Functions and Algorithms

////////////////////////////////////////////////////////////////////////////////////

// content : Insertion and Merge Sort Algorithms
//
// content : Algorithmic Complexities O(N^2) and O(N*log(N))
//
// content : Timsort Algorithm
//
// content : Cache Lines
//
// content : Function std::midpoint

////////////////////////////////////////////////////////////////////////////////////

// support : www.cs.usfca.edu/~galles/visualization/ComparisonSort.html

////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////

void order(std::vector < int > & vector, std::size_t left, std::size_t right)
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

////////////////////////////////////////////////////////////////////////////////////

void merge(std::vector < int > & vector_1, std::size_t left, std::size_t right)
{
	auto middle = std::midpoint(left, right), size = right - left;

	std::vector < int > vector_2(size, 0);

	for (auto i = left, j = middle, k = 0uz; k < size; ++k) 
	{
		if (i < middle && ((j < right && vector_1[i] <= vector_1[j]) || j == right))
		{
			vector_2[k] = vector_1[i++];
		}
		else
		{
			vector_2[k] = vector_1[j++];
		}
	}

	for (auto i = 0uz, j = 0uz; j < size; ++j) 
	{
		vector_1[left + i++] = vector_2[j];
	}
}

////////////////////////////////////////////////////////////////////////////////////

void split(std::vector < int > & vector, std::size_t left, std::size_t right)
{
	if (right - left > 16)
	{
		auto middle = std::midpoint(left, right);

		split(vector, left,   middle);
		
		split(vector, middle, right );

		merge(vector, left,   right );
	}
	else
	{
		order(vector, left,   right );
	}
}

////////////////////////////////////////////////////////////////////////////////////

void sort(std::vector < int > & vector)
{
	split(vector, 0, std::size(vector));
}

////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////