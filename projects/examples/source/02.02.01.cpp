#include <cassert>

/////////////////////////////

int main()
{
	auto x = false, y = true;

//  -------------------------

	assert(!x == y);

	assert(!y == x);

//  -------------------------

	assert((x && x) == x);

	assert((x && y) == x);

	assert((y && x) == x);

	assert((y && y) == y);

//  -------------------------

	assert((x || x) == x);
	
	assert((x || y) == y);

	assert((y || x) == y);

	assert((y || y) == y);
}
