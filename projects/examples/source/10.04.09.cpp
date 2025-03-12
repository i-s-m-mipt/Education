#include <cassert>

#include <boost/bimap.hpp>

///////////////////////////////////////////////////////////////////////////

int main()
{
    boost::bimap < int, int > map; // support: boost::bimaps::(multi)set_of

//  -----------------------------------------------------------------------

	map.insert({ 1, 1 });

//  -----------------------------------------------------------------------

	assert(map.left.count(1) == map.right.count(1));

//  -----------------------------------------------------------------------

	for (const auto & element : map) 
	{
		assert(element.left == element.right);
	}
}