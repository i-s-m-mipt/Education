#include <cassert>
#include <cmath>
#include <concepts>
#include <string>
#include <type_traits>

using namespace std::literals;

//  ================================================================================================

template < typename T > concept integral = std::is_integral_v < T > ;

template < typename T > concept floating_point = std::is_floating_point_v < T > ;

template < typename T > concept arithmetic = integral < T > || floating_point < T > ;

//  ================================================================================================

template < typename T > concept addable = requires (T x, T y) { x + y; };

template < typename T > concept equable = requires (T x, T y)
{
    { x == y } -> std::convertible_to < bool > ;
    { x != y } -> std::convertible_to < bool > ;
};

template < typename T > concept ordable = equable < T > && requires (T x, T y)
{
    { x <  y } -> std::convertible_to < bool > ;
    { x <= y } -> std::convertible_to < bool > ;
    { x >  y } -> std::convertible_to < bool > ;
    { x >= y } -> std::convertible_to < bool > ;
};

template < typename T > concept typable = requires 
{ 
    typename T::value_type; 
};

//  ================================================================================================

template < typename T > [[nodiscard]] auto max_v1(T x, T y) requires integral < T >
{
	return x < y ? y : x;
}

[[nodiscard]] auto max_v2(integral auto x, integral auto y)
{
	return x < y ? y : x;
}

template < integral T > [[nodiscard]] auto max_v3(T x, T y)
{
	return x < y ? y : x;
}

//  ================================================================================================

template < typename T > requires std::regular < T > struct Entity {};

//  ================================================================================================

int main()
{
    assert(max_v1(1, 2) == 2);
    assert(max_v2(1, 2) == 2);
    assert(max_v3(1, 2) == 2);

//  ------------------------------------------------------------------------------------------------
 
//  assert(max_v1("aaaaa"s, "bbbbb"s) == "bbbbb"s); // error
//  assert(max_v2("aaaaa"s, "bbbbb"s) == "bbbbb"s); // error
//  assert(max_v3("aaaaa"s, "bbbbb"s) == "bbbbb"s); // error

//  ------------------------------------------------------------------------------------------------

    [[maybe_unused]] Entity < int   > entity_1;
//  [[maybe_unused]] Entity < int & > entity_2; // error
}