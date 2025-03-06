#include <cassert>
#include <limits>

////////////////////////////////////////////////////////////

int main()
{
    float x = 1.0f; double y = 2.0; long double z = 3.0l;

//  --------------------------------------------------------

	static_assert(sizeof(x) == 4);

	static_assert(sizeof(y) == 8);

	static_assert(sizeof(z) >= 8);

//  --------------------------------------------------------

	assert(std::numeric_limits < double > ::digits10 == 15);
}