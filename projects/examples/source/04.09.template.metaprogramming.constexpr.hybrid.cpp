#include <iostream>

//  ================================================================================================

template < auto N, auto D = 1 > class Ratio
{
public:

	static constexpr auto num = N;
	static constexpr auto den = D;

	using type = Ratio < num, den > ;

}; // template < auto N, auto D = 1 > class Ratio

//  ================================================================================================

template < typename R1, typename R2 > class Add
{
private:

	static constexpr auto num = R1::num * R2::den + R2::num * R1::den;
	static constexpr auto den = R1::den * R2::den;

public:

	using type = Ratio < num, den > ;

}; // template < typename R1, typename R2 > class Add

template < typename R1, typename R2 > using add_t = typename Add < R1, R2 > ::type;

//  ================================================================================================

template < typename T, typename R = Ratio < 1 > > struct Duration { T value{}; };

//  ================================================================================================

template < typename T1, typename R1, typename T2, typename R2 > 

[[nodiscard]] inline constexpr auto operator+(Duration < T1, R1 > lhs, Duration < T2, R2 > rhs)
{
	using unit_t = Ratio < 1, add_t < R1, R2 > ::den > ;

	const auto value = lhs.value * unit_t::den / R1::den * R1::num +
					   rhs.value * unit_t::den / R2::den * R2::num;

	return Duration < decltype(value), unit_t > { value };
}

//  ================================================================================================

int main()
{
	constexpr auto result = Duration < int, Ratio < 2, 5 > > (1) +
							Duration < int, Ratio < 3, 7 > > (2);

	std::cout << result.value << std::endl;

	return 0;
}