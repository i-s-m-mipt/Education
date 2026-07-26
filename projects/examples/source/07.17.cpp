////////////////////////////////////////////////////////////////////////////////////

// chapter : Debugging and Profiling Tools

////////////////////////////////////////////////////////////////////////////////////

// content : Profiling
//
// content : Hardware Events
//
// content : Performance Counters
//
// content : Tool perf

////////////////////////////////////////////////////////////////////////////////////

// support : sudo perf record -e cycles -c 1000 ./07.17
//
// support : sudo perf annotate --objdump="objdump -M intel" > output.asm

////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////

__attribute__((noinline)) void order
(
	std::vector < int > & vector, std::size_t left, std::size_t right
)
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

__attribute__((noinline)) void merge
(
	std::vector < int > & vector_1, std::size_t left, std::size_t right
)
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

__attribute__((noinline)) void split
(
	std::vector < int > & vector, std::size_t left, std::size_t right
)
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

__attribute__((noinline)) void sort(std::vector < int > & vector)
{
	split(vector, 0, std::size(vector));
}

////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto size = 1uz << 30;

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