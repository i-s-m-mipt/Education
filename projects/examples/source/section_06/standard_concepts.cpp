#include <concepts>

template < typename T > [[nodiscard]] inline constexpr T max(T x, T y) requires std::integral < T >
{
	return (x < y ? y : x);
}

template < std::floating_point ... Ts > [[nodiscard]] inline constexpr auto sum(Ts ... args)
{
	return (... + args);
}

template < typename T > requires std::regular < T > class Container {};

int main()
{
    [[maybe_unused]] constexpr auto result_1 = max(1, 2);

//  constexpr auto result_2 = max(1.0, 2.0); // error: constraints not satisfied

    [[maybe_unused]] constexpr auto result_3 = sum(1.0, 2.0);

//  constexpr auto result_4 = sum(1, 2); // error: constraints not satisfied

    [[maybe_unused]] constexpr Container < int > container_1;

//  constexpr Container < int & > container_2; // error: template constraint failure

    return 0;
}