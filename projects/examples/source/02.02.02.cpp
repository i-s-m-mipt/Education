#include <cassert>

///////////////////////////

int main()
{
	auto x = 1, y = 2;

//  -----------------------

	assert((x +  y) == +3);
	
	assert((x -  y) == -1);

	assert((x *  y) == +2);

	assert((x /  y) == +0);

	assert((x %  y) == +1);

//  -----------------------

	assert((x += y) == +3);

	assert((x -= y) == +1);

	assert((x *= y) == +2);

	assert((x /= y) == +1);

	assert((x %= y) == +1);

//  -----------------------

	assert((x ++  ) == +1);

	assert((  ++ y) == +3);

	assert((x --  ) == +2);

	assert((  -- y) == +2);

//  -----------------------

	assert((x <  y) ==  1);

	assert((x >  y) ==  0);

	assert((x <= y) ==  1);

	assert((x >= y) ==  0);

	assert((x == y) ==  0);

	assert((x != y) ==  1);
}