#include <concepts>
#include <type_traits>

// =================================================================================================

template < typename T > concept integral = std::is_integral_v < T > ;

template < typename T > concept floating_point = std::is_floating_point_v < T > ;

template < typename T > concept arithmetic = (integral < T > || floating_point < T > );

// =================================================================================================

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
    typename T::value_type; // note: required nested member name
};

// =================================================================================================

template < typename T > [[nodiscard]] inline constexpr T max_v1(T x, T y) requires integral < T >
{
	return (x < y ? y : x);
}

[[nodiscard]] inline constexpr integral auto max_v2(integral auto x, integral auto y)
{
	return (x < y ? y : x);
}

template < integral ... Ts > [[nodiscard]] inline constexpr integral auto sum_v1(Ts ... args)
{
	return (... + args);
}

template < typename T > requires std::regular < T > class Container {}; // note: standard concept

// =================================================================================================

int main()
{
    [[maybe_unused]] constexpr auto result_1 = max_v1(1, 2);

//  constexpr auto result_2 = max_v1(1.0, 2.0); // error: constraints not satisfied

    [[maybe_unused]] constexpr auto result_3 = max_v2(1, 2);

//  constexpr auto result_4 = max_v2(1.0, 2.0); // error: constraints not satisfied

    [[maybe_unused]] constexpr auto result_5 = sum_v1(1, 2);

//  constexpr auto result_6 = sum_v1(1.0, 2.0); // error: constraints not satisfied

    [[maybe_unused]] constexpr Container < int > container_1;

//  constexpr Container < int & > container_2; // error: template constraint failure

    return 0;
}