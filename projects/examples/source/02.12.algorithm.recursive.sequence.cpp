#include <cassert>
#include <cmath>
#include <cstddef>

///////////////////////////////////////////////////////////////////////////////////////////

auto count_v1(std::size_t size, std::size_t left = 0, std::size_t right = 0) -> std::size_t
{
	auto counter = 0uz;

	if (left < size || right < size)
	{
		if (left < size) 
		{ 
			counter += count_v1(size, left + 1, right); 
		}

		if (left > right) 
		{ 
			counter += count_v1(size, left, right + 1); 
		}
	}
	
	return counter > 0 ? counter : 1uz;
}

///////////////////////////////////////////////////////////////////////////////////////////

auto count_v2(std::size_t size, std::size_t left = 0, std::size_t right = 0) -> std::size_t
{
	auto counter = 0uz;

	if (left < size)
	{
		for (auto i = size; i > std::max(left, right + 1) - 1; --i) 
		{
			counter += count_v2(size, i, right + 1);
		}
	}

	return counter > 0 ? counter : 1uz;
}

///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	assert(count_v1(5) == 42);
	
	assert(count_v2(5) == 42);
}