/////////////////////////////////////////////////////////////////////

#include <concepts>

/////////////////////////////////////////////////////////////////////

template < typename T > concept totally_ordered = requires (T x, T y)
{
    { x <  y } -> std::convertible_to < bool > ;
    
    { x >  y } -> std::convertible_to < bool > ;

    { x <= y } -> std::convertible_to < bool > ;

    { x >= y } -> std::convertible_to < bool > ;

    { x == y } -> std::convertible_to < bool > ;

    { x != y } -> std::convertible_to < bool > ;
};

/////////////////////////////////////////////////////////////////////

struct Entity {};

/////////////////////////////////////////////////////////////////////

int main()
{
    static_assert(     totally_ordered < int    > == 1);
    
    static_assert(     totally_ordered < Entity > == 0);

//  ----------------------------------------------------

    static_assert(std::totally_ordered < int    > == 1);
    
    static_assert(std::totally_ordered < Entity > == 0);
}

/////////////////////////////////////////////////////////////////////