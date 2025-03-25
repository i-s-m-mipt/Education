#include <cassert>

#include <boost/bimap.hpp>

/////////////////////////////////////////////////////////////////////////////

int main()
{
    boost::bimap < int, int > bimap; // support : boost::bimaps::(multi)set_of

//  -------------------------------------------------------------------------

	bimap.insert({ 1, 1 });

//  -------------------------------------------------------------------------

	assert(bimap.left.count(1) == bimap.right.count(1));

//  -------------------------------------------------------------------------

	for (const auto & element : bimap) 
	{
		assert(element.left == element.right);
	}
}