#include <type_traits>

///////////////////////////////////////////////////////////////

template 
< 
	typename T, typename ... Ts 
> 
constexpr auto is_any_of_v = (std::is_same_v < T, Ts > || ...);

///////////////////////////////////////////////////////////////

template 
< 
	typename T, typename ... Ts 
> 
constexpr auto is_all_of_v = (std::is_same_v < T, Ts > && ...);

///////////////////////////////////////////////////////////////

int main()
{
    static_assert(is_any_of_v < int, int,    double > == 1);

    static_assert(is_any_of_v < int, double, double > == 0);

//  --------------------------------------------------------

    static_assert(is_all_of_v < int, int,    int    > == 1);

	static_assert(is_all_of_v < int, int,    double > == 0);
}
