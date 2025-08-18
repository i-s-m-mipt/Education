/////////////////////////////////////////////////////////////

#include <type_traits>

/////////////////////////////////////////////////////////////

int main()
{
    auto x1 = 1, & x2 = x1, x3 = x2;

//  ---------------------------------------------------------

    decltype(auto) x4 = x2;

//  ---------------------------------------------------------

	static_assert(std::is_same_v < decltype( x1 ), int   > );

    static_assert(std::is_same_v < decltype( x2 ), int & > );

    static_assert(std::is_same_v < decltype( x3 ), int   > );

    static_assert(std::is_same_v < decltype( x4 ), int & > );

//  ---------------------------------------------------------

    static_assert(std::is_same_v < decltype((x1)), int & > );
}

/////////////////////////////////////////////////////////////