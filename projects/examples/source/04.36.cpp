/////////////////////////////////////////////////////////////////////////

// chapter : Generic Programming

/////////////////////////////////////////////////////////////////////////

// section : Constraints and Concepts

/////////////////////////////////////////////////////////////////////////

// content : Expression requires
//
// content : Simple and Type Requirements
//
// content : Concept range
//
// content : Concepts sized_range and std::ranges::sized_range

/////////////////////////////////////////////////////////////////////////

#include <concepts>
#include <ranges>
#include <vector>

/////////////////////////////////////////////////////////////////////////

template < typename R > concept range = requires (R range)
{
	std::begin(range);

	std::end  (range);
};

/////////////////////////////////////////////////////////////////////////

template < typename R > concept sized_range = 
(
    range < R > && requires (R range){ std::size(range); }
);

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