#include <cassert>
#include <cmath>
#include <utility>

int main()
{
	auto f = false, t = true;

//  -------------------------

	assert(!f == t);
	assert(!t == f);

//  ----------------------

	assert((f && f) == f);
	assert((f && t) == f);
	assert((t && f) == f);
	assert((t && t) == t);

//  ----------------------

	assert((f || f) == f);
	assert((f || t) == t);
	assert((t || f) == t);
	assert((t || t) == t);

//  --------------------------------

	assert(!(f && t) == (!f || !t));
	assert(!(f || t) == (!f && !t));

//  --------------------------------

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

	assert((x <  y) ==  t);
	assert((x >  y) ==  f);
	assert((x <= y) ==  t);
	assert((x >= y) ==  f);
	assert((x == y) ==  f);
	assert((x != y) ==  t);
	
//  ---------------------------------------------------------------------------

//	assert((static_cast < bool > (x) != static_cast < bool > (y)) == f); // bad

	assert((!!x != !!y) == f);

//  --------------------------

	std::swap(x, y);

	x = x + y; 
	y = x - y; 
	x = x - y;

//  -------------------------------------------

	assert(std::abs(1.0 * x / y - 0.5) < 1e-6);

	assert(+x % +y ==  1);
	assert(+x % -y ==  1);
	assert(-x % +y == -1);
	assert(-x % -y == -1);

//  ----------------------

//	x++++; // error

//	assert((++x, ++y) == 2); // bad

//  -------------------------------

	x = (1 + 2) / (3 + 4);

//	x = x + ++x; // error

	x = y = 1 + 2 + 3;
}
