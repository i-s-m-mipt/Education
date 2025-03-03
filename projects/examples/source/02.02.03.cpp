#include <cassert>

///////////////////////////////////////////////////////////////////////////

int main()
{
    auto x = 1, y = 2;

//	assert(!(static_cast < bool > (x) != static_cast < bool > (y))); // bad

	assert(!(!!x != !!y));
}