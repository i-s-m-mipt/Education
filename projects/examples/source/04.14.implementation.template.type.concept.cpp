#include <concepts>
#include <type_traits>

//  ================================================================================================

template < typename T > concept integral = std::is_integral_v < T > ;

template < typename T > concept floating_point = std::is_floating_point_v < T > ;

template < typename T > concept arithmetic = (integral < T > || floating_point < T > );

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

template < typename T > concept typable = requires { typename T::value_type; };

//  ================================================================================================

template < typename T > [[nodiscard]] inline constexpr T max_v1(T x, T y) requires integral < T >
{
	return (x < y ? y : x);
}

[[nodiscard]] inline constexpr integral auto max_v2(integral auto x, integral auto y)
{
	return (x < y ? y : x);
}

template < integral T > [[nodiscard]] inline constexpr integral auto max_v3(T x, T y)
{
	return (x < y ? y : x);
}

//  ================================================================================================

template < typename T > requires std::regular < T > class Container {};

//  ================================================================================================

int main()
{
    static_assert(max_v1(100, 200) == 200);
//  static_assert(max_v1(1.0, 2.0) == 2.0); // error

    static_assert(max_v2(100, 200) == 200);
//  static_assert(max_v2(1.0, 2.0) == 2.0); // error

    static_assert(max_v3(100, 200) == 200);
//  static_assert(max_v3(1.0, 2.0) == 2.0); // error

//  ================================================================================================

    [[maybe_unused]] constexpr Container < int   > container_1;
//  [[maybe_unused]] constexpr Container < int & > container_2; // error

    return 0;
}