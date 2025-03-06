#include <cassert>
#include <limits>

//////////////////////////////////////////////////////////////////

int main()
{
	short x = 1; int y = 2; long z = 3l;

//  --------------------------------------------------------------

	static_assert(sizeof(x) == 2);

	static_assert(sizeof(y) == 4);

	static_assert(sizeof(z) == 8);

//  --------------------------------------------------------------

	assert(std::numeric_limits < int > ::max() == +2'147'483'647);
		
	assert(std::numeric_limits < int > ::min() == -2'147'483'648);
}