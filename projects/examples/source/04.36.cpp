/////////////////////////////////////////////////////////////////////////

#include <concepts>
#include <ranges>
#include <vector>

/////////////////////////////////////////////////////////////////////////

template < typename R > concept sized_range = requires (R range)
{
	std::ranges::begin(range);

	std::ranges::end  (range);

    std::ranges::size (range);

//  --------------------------

    typename R::iterator;
};

/////////////////////////////////////////////////////////////////////////

int main()
{
    static_assert(             sized_range < std::vector < int > > == 1);
    
    static_assert(             sized_range < int                 > == 0);

//  ---------------------------------------------------------------------

    static_assert(std::ranges::sized_range < std::vector < int > > == 1);
    
    static_assert(std::ranges::sized_range < int                 > == 0);
}

/////////////////////////////////////////////////////////////////////////