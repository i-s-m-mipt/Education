#include <cassert>

//////////////////////////

int main()
{
	bool x = 0, y = 1;

//  ----------------------

	assert(!x == y);

	assert(!y == x);

//  ----------------------

	assert((x && x) == x);

	assert((x && y) == x);

	assert((y && x) == x);

	assert((y && y) == y);

//  ----------------------

	assert((x || x) == x);
	
	assert((x || y) == y);

	assert((y || x) == y);

	assert((y || y) == y);
}
