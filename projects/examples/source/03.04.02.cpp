#include <cassert>
#include <cmath>
#include <iostream>

#include <boost/rational.hpp>

//////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

//////////////////////////////////////////////////////////////////////////

int main()
{
    boost::rational < int > x = 1, y = 2;

//  ----------------------------------------------------------------------

	assert(equal(boost::rational_cast < double > (x), 1.0));

//  ----------------------------------------------------------------------

	assert((x += y) == boost::rational < int > (+3, 1));
	assert((x -= y) == boost::rational < int > (+1, 1));
	assert((x *= y) == boost::rational < int > (+2, 1));
	assert((x /= y) == boost::rational < int > (+1, 1));

//  ----------------------------------------------------------------------

	assert((x ++  ) == boost::rational < int > (+1, 1));
	assert((  ++ y) == boost::rational < int > (+3, 1));
	assert((x --  ) == boost::rational < int > (+2, 1));
	assert((  -- y) == boost::rational < int > (+2, 1));

//  ----------------------------------------------------------------------

	assert((x +  y) == boost::rational < int > (+3, 1));
	assert((x -  y) == boost::rational < int > (-1, 1));
	assert((x *  y) == boost::rational < int > (+2, 1));
	assert((x /  y) == boost::rational < int > (+1, 2));

//  ----------------------------------------------------------------------

	assert((x += 1) == boost::rational < int > (+2, 1));
	assert((x +  1) == boost::rational < int > (+3, 1));
	assert((1 +  y) == boost::rational < int > (+3, 1));
	assert((1 +  1) == boost::rational < int > (+2, 1));

//  ----------------------------------------------------------------------

	assert((x <  y) == 0);
	assert((x >  y) == 0);
	assert((x <= y) == 1);
	assert((x >= y) == 1);
	assert((x == y) == 1);
	assert((x != y) == 0);

//  ----------------------------------------------------------------------

	std::cout << "main : enter boost::rational < int > : "; std::cin >> x;
	
	std::cout << "main : x = " << x << '\n';
}