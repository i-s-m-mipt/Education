#include <cassert>
#include <cmath>
#include <utility>

///////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		auto x = false, y = true;

		assert(!x == y);
		assert(!y == x);

		assert((x && x) == x);
		assert((x && y) == x);
		assert((y && x) == x);
		assert((y && y) == y);

		assert((x || x) == x);
		assert((x || y) == y);
		assert((y || x) == y);
		assert((y || y) == y);
	}
	
//  ---------------------------------------------------------------------------

	{
		auto x = 1, y = 2;

		assert((x +  y) == +3);
		assert((x -  y) == -1);
		assert((x *  y) == +2);
		assert((x /  y) == +0);
		assert((x %  y) == +1);

		assert((x += y) == +3);
		assert((x -= y) == +1);
		assert((x *= y) == +2);
		assert((x /= y) == +1);
		assert((x %= y) == +1);

		assert((x ++  ) == +1);
		assert((  ++ y) == +3);
		assert((x --  ) == +2);
		assert((  -- y) == +2);

		assert((x <  y) ==  1);
		assert((x >  y) ==  0);
		assert((x <= y) ==  1);
		assert((x >= y) ==  0);
		assert((x == y) ==  0);
		assert((x != y) ==  1);
	}

//  ---------------------------------------------------------------------------

	{
		auto x = 1, y = 2;

//		assert(!(static_cast < bool > (x) != static_cast < bool > (y))); // bad

		assert(!(!!x != !!y));
	}

//  ---------------------------------------------------------------------------

	{
		auto x = 1, y = 2;

		std::swap(x, y);

		assert(x == 2 && y == 1);

		x = x + y; 
		y = x - y; 
		x = x - y;

		assert(x == 1 && y == 2);
	}

//  ---------------------------------------------------------------------------	

	{
		auto x = 1, y = 2;

		assert(std::abs(1.0 * x / y - 0.5) < 1e-6);

		assert(+x % +y == +1);
		assert(+x % -y == +1);
		assert(-x % +y == -1);
		assert(-x % -y == -1);
	}

//  ---------------------------------------------------------------------------

	{
		auto x = (1 + 2) / (3 + 4);

//		x = x + ++x; // error

		[[maybe_unused]] auto y = x = 1 + 2 + 3;

//		assert((++x, ++y) == 7); // bad
	}
}
