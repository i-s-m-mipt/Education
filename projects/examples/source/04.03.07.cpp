#include <cassert>
#include <type_traits>

//////////////////////////////////////////////////////////////////////////////////////////

template < int N = 0, int D = 1 > struct Ratio
{
	static constexpr auto num = N;
	
	static constexpr auto den = D;
};

//////////////////////////////////////////////////////////////////////////////////////////

template < typename R1, typename R2 > struct Sum
{
	static constexpr auto num = R1::num * R2::den + R2::num * R1::den;

	static constexpr auto den = R1::den * R2::den;

//  ------------------------------------------------------------------
	
	using type = Ratio < num, den > ;
};

//////////////////////////////////////////////////////////////////////////////////////////

template < typename R1, typename R2 > using sum = typename Sum < R1, R2 > ::type;

//////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename R = Ratio < 1 > > struct Duration 
{
	T x = T();
};

//////////////////////////////////////////////////////////////////////////////////////////

template 
< 
	typename T1, typename R1, 
	
	typename T2, typename R2 
>
constexpr auto operator+(const Duration < T1, R1 > & lhs, const Duration < T2, R2 > & rhs)
{
	using ratio_t = Ratio < 1, sum < R1, R2 > ::den > ;

//  ---------------------------------------------------

	auto x = 
	(
		lhs.x * ratio_t::den / R1::den * R1::num +

		rhs.x * ratio_t::den / R2::den * R2::num
	);

//  ---------------------------------------------------

	return Duration < decltype(x), ratio_t > (x);
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Duration < int, Ratio < 1, 2 > > duration_1(1);

	Duration < int, Ratio < 1, 3 > > duration_2(1);

//  ----------------------------------------------------------------------

	Duration < int, Ratio < 1, 6 > > duration_3 = duration_1 + duration_2;

//  ----------------------------------------------------------------------

	assert(duration_3.x == 5);
}