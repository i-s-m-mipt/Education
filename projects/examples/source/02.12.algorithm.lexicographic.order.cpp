#include <cassert>
#include <cmath>

//  ================================================================================================

std::size_t count_v1(std::size_t s, std::size_t l = 0, std::size_t r = 0) 
{
	if (l < s || r < s)
	{
		std::size_t c = 0;
		
		if (l < s) c += count_v1(s, l + 1, r    );
		if (l > r) c += count_v1(s, l    , r + 1);

		return c;
	}
	
	return 1;
}

//  ================================================================================================

std::size_t count_v2(std::size_t s, std::size_t l = 0, std::size_t r = 0) 
{
	if (l < s)
	{
		std::size_t c = 0;

		for (auto i = s; i > std::max(l, r + 1) - 1; --i) 
		{
			c += count_v2(s, i, r + 1);
		}

		return c;
	}

	return 1;
}

//  ================================================================================================

int main()
{
	assert(count_v1(1) ==  1 && count_v2(1) ==  1);
	assert(count_v1(2) ==  2 && count_v2(2) ==  2);
	assert(count_v1(3) ==  5 && count_v2(3) ==  5);
	assert(count_v1(4) == 14 && count_v2(4) == 14);
	assert(count_v1(5) == 42 && count_v2(5) == 42);

	return 0;
}