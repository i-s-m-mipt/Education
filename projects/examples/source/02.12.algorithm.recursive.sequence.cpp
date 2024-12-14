#include <cassert>
#include <cmath>
#include <cstddef>

//  ================================================================================================

auto count_v1(std::size_t size, std::size_t n_left = 0, std::size_t n_right = 0) -> std::size_t
{
	if (auto counter = 0uz; n_left < size || n_right < size)
	{
		if (n_left < size) 
		{ 
			counter += count_v1(size, n_left + 1, n_right); 
		}

		if (n_left > n_right) 
		{ 
			counter += count_v1(size, n_left, n_right + 1); 
		}

		return counter;
	}
	
	return 1;
}

//  ================================================================================================

auto count_v2(std::size_t size, std::size_t n_left = 0, std::size_t n_right = 0) -> std::size_t
{
	if (auto counter = 0uz; n_left < size)
	{
		for (auto i = size; i > std::max(n_left, n_right + 1) - 1; --i) 
		{
			counter += count_v2(size, i, n_right + 1);
		}

		return counter;
	}

	return 1;
}

//  ================================================================================================

int main()
{
	assert(count_v1(5) == 42);
	assert(count_v2(5) == 42);
}