//////////////////////////////////////////////////////////////////

#include <cassert>
#include <limits>

//////////////////////////////////////////////////////////////////

int main()
{
	short x1 = 1; int x2 = 2; long x3 = 3l; long long x4 = 4ll;

//  --------------------------------------------------------------

	static_assert(sizeof(x1) == 2);

	static_assert(sizeof(x2) == 4);

	static_assert(sizeof(x3) == 8);

	static_assert(sizeof(x4) == 8);

//  --------------------------------------------------------------

	assert(std::numeric_limits < int > ::max() == +2'147'483'647);
		
	assert(std::numeric_limits < int > ::min() == -2'147'483'648);
}

//////////////////////////////////////////////////////////////////