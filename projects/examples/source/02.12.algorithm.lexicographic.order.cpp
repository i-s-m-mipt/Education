#include <cassert>
#include <cmath>

//  ================================================================================================

std::size_t count_slow(std::size_t size, std::size_t left = 0, std::size_t right = 0) 
{
	if (left < size || right < size)
	{
		std::size_t counter = 0;

		if (left < size) 
		{ 
			counter += count_slow(size, left + 1, right); 
		}

		if (right < left) 
		{ 
			counter += count_slow(size, left, right + 1); 
		}

		return counter;
	}
	else 
	{ 
		return 1; 
	} 	
}

//  ================================================================================================

std::size_t count_fast(std::size_t size, std::size_t left = 0, std::size_t right = 0) 
{
	if (left < size)
	{
		std::size_t counter = 0;

		for (auto i = size; i > std::max(left, right + 1) - 1; --i)
		{
			counter += count_fast(size, i, right + 1);
		}

		return counter;
	}
	else
	{
		return 1;
	}
}

//  ================================================================================================

int main()
{
	assert(count_slow(0) ==    1 && count_fast(0) ==    1);
	assert(count_slow(1) ==    1 && count_fast(1) ==    1);
	assert(count_slow(2) ==    2 && count_fast(2) ==    2);
	assert(count_slow(3) ==    5 && count_fast(3) ==    5);
	assert(count_slow(4) ==   14 && count_fast(4) ==   14);
	assert(count_slow(5) ==   42 && count_fast(5) ==   42);
	assert(count_slow(6) ==  132 && count_fast(6) ==  132);
	assert(count_slow(7) ==  429 && count_fast(7) ==  429);
	assert(count_slow(8) == 1430 && count_fast(8) == 1430);
	assert(count_slow(9) == 4862 && count_fast(9) == 4862);

	return 0;
}