#include <type_traits>

////////////////////////////////////////////////////////////

int main()
{
    auto x = 1, & r_x_1 = x, y = r_x_1;

//  --------------------------------------------------------

	static_assert(std::is_same_v < decltype( x ), int   > );

    static_assert(std::is_same_v < decltype( y ), int   > );

    static_assert(std::is_same_v < decltype((x)), int & > );

//  --------------------------------------------------------

	decltype(auto) r_x_2 = r_x_1;

//  --------------------------------------------------------

    static_assert(std::is_reference_v < decltype(r_x_1) > );

    static_assert(std::is_reference_v < decltype(r_x_2) > );
}