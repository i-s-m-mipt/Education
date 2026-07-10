/////////////////////////////////////////////////////////////////////////////

// chapter : Generic Programming

/////////////////////////////////////////////////////////////////////////////

// content : Expression requires
//
// content : Concepts range and sized_range

/////////////////////////////////////////////////////////////////////////////

#include <concepts>
#include <iterator>
#include <ranges>
#include <vector>

/////////////////////////////////////////////////////////////////////////////

template < typename R > concept range = requires (R range)
{
	std::begin(range);

	std::end  (range);
};

/////////////////////////////////////////////////////////////////////////////

template
<
    typename R
>
concept sized_range = range < R > && requires (R range){ std::size(range); };

/////////////////////////////////////////////////////////////////////////////

int main()
{
    static_assert(                   range < std::vector < int > > == 1);

    static_assert(                   range < int                 > == 0);

//  ---------------------------------------------------------------------

    static_assert(std::ranges::      range < std::vector < int > > == 1);

    static_assert(std::ranges::      range < int                 > == 0);

//  ---------------------------------------------------------------------

    static_assert(             sized_range < std::vector < int > > == 1);

    static_assert(             sized_range < int                 > == 0);

//  ---------------------------------------------------------------------

    static_assert(std::ranges::sized_range < std::vector < int > > == 1);

    static_assert(std::ranges::sized_range < int                 > == 0);
}

/////////////////////////////////////////////////////////////////////////////