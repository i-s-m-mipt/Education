#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

///////////////////////////////////////////////////

int main()
{
	auto size = 5uz;

	std::vector < int > vector(size, 0);

	for (auto i = size; i > 0; --i)
	{
		vector[size - i] = static_cast < int > (i);
	}

//  -----------------------------------------------

	for (auto i = 0uz; i < size - 1; ++i)
	{
		for (auto j = i + 1; j < size; ++j)
		{
			if (vector[i] > vector[j]) 
			{
				std::swap(vector[i], vector[j]);
			}
		}
	}

//  -----------------------------------------------

	assert(std::ranges::is_sorted(vector));
}