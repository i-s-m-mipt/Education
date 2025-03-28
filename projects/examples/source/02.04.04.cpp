/////////////////////////////////////////////////////////////////

#include <cassert>

/////////////////////////////////////////////////////////////////

inline auto max_v1(int x, int y)
{ 
	return x > y ? x : y;
}

/////////////////////////////////////////////////////////////////

__attribute__ ((__noinline__)) auto max_v2(int x, int y)
{
	return x > y ? x : y;
}

/////////////////////////////////////////////////////////////////

int main()
{
	volatile auto x = 1, y = 2;

//  -------------------------------------------------------------

	assert(max_v1(x, y) == 2); // support : compiler-explorer.com
		
	assert(max_v2(x, y) == 2); // support : compiler-explorer.com

	assert(max_v1(1, 2) == 2); // support : compiler-explorer.com

	assert(max_v2(1, 2) == 2); // support : compiler-explorer.com
}

/////////////////////////////////////////////////////////////////