//////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <limits>
#include <type_traits>
#include <utility>

//////////////////////////////////////////////////////////////////////////

int main()
{
    int x = 1; signed int y = 2; unsigned int z = 3u;

//  ----------------------------------------------------------------------

	static_assert(sizeof(x) == sizeof(y));

	static_assert(sizeof(x) == sizeof(z));

//  ----------------------------------------------------------------------

	static_assert(std::is_same_v < signed int, int > );

//  ----------------------------------------------------------------------

	assert(std::numeric_limits < unsigned int > ::max() == 4'294'967'295);

	assert(std::numeric_limits < unsigned int > ::min() == 0);

//  ----------------------------------------------------------------------

#pragma GCC diagnostic ignored "-Wsign-compare"

//  ----------------------------------------------------------------------

    assert(-1 > 1u && std::cmp_less(-1, 1u) && std::cmp_equal(1, 1u));
}

//////////////////////////////////////////////////////////////////////////