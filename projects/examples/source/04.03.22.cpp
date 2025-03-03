#include <concepts>

////////////////////////////////////////////////////////////////

template < typename T > concept comparable = requires (T x, T y)
{
    { x <  y } -> std::convertible_to < bool > ;
    
    { x >  y } -> std::convertible_to < bool > ;

    { x <= y } -> std::convertible_to < bool > ;

    { x >= y } -> std::convertible_to < bool > ;

    { x == y } -> std::convertible_to < bool > ;

    { x != y } -> std::convertible_to < bool > ;
};

////////////////////////////////////////////////////////////////

struct Entity {};

////////////////////////////////////////////////////////////////

int main()
{
    static_assert( comparable < int    > );
    
    static_assert(!comparable < Entity > );
}