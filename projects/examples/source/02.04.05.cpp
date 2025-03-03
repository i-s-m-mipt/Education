#include <cassert>
#include <cmath>
#include <cstddef>

/////////////////////////////////////////////////////////////////////////////////////////////

auto factorial(int x) -> int 
{ 
	return x > 1 ? x * factorial(x - 1) : 1; 
}

/////////////////////////////////////////////////////////////////////////////////////////////

auto C_v1(int x, int y)
{
	return x < y ? 0 : factorial(x) / factorial(y) / factorial(x - y);
}

/////////////////////////////////////////////////////////////////////////////////////////////

auto C_v2(int x, int y) -> int
{
	return x < y ? 0 : x == y || y == 0 ? 1 : C_v2(x - 1, y - 1) + C_v2(x - 1, y);
}

/////////////////////////////////////////////////////////////////////////////////////////////

auto catalan_v1(int x) { return C_v1(2 * x, x) / (x + 1); }

auto catalan_v2(int x) { return C_v2(2 * x, x) - C_v2(x * x, x - 1); }

/////////////////////////////////////////////////////////////////////////////////////////////

auto catalan_v3(std::size_t size, std::size_t left = 0, std::size_t right = 0) -> std::size_t
{
	auto counter = 0uz;

	if (left < size || right < size)
	{
		if (left < size)
		{ 
			counter += catalan_v3(size, left + 1, right);
		}

		if (left > right)
		{ 
			counter += catalan_v3(size, left, right + 1);
		}
	}
	
	return counter > 0 ? counter : 1uz;
}

/////////////////////////////////////////////////////////////////////////////////////////////

auto catalan_v4(std::size_t size, std::size_t left = 0, std::size_t right = 0) -> std::size_t
{
	auto counter = 0uz;

	if (left < size)
	{
		for (auto i = size; i > std::max(left, right + 1) - 1; --i)
		{
			counter += catalan_v4(size, i, right + 1);
		}
	}

	return counter > 0 ? counter : 1uz;
}

/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	assert(catalan_v1(5) == 42);
	
	assert(catalan_v2(5) == 42);

	assert(catalan_v3(5) == 42);
	
	assert(catalan_v4(5) == 42);
}