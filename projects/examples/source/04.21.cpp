//////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>

//////////////////////////////////////////////////////////////////////////////////////////

template < int N = 0, int D = 1 > struct Ratio
{
	constexpr static auto num = N;
	
	constexpr static auto den = D;
};

//////////////////////////////////////////////////////////////////////////////////////////

template < typename R1, typename R2 > struct Sum
{
	constexpr static auto num = R1::num * R2::den + R2::num * R1::den;

	constexpr static auto den = R1::den * R2::den;

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
constexpr auto operator+(Duration < T1, R1 > const & lhs, Duration < T2, R2 > const & rhs)
{
	using ratio_t = Ratio < 1, sum < R1, R2 > ::den > ;

	auto x = 
	(
		lhs.x * ratio_t::den / R1::den * R1::num +

		rhs.x * ratio_t::den / R2::den * R2::num
	);

	return Duration < decltype(x), ratio_t > (x);
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto x = 1, y = 2;

//  ----------------------------------------------------------------------

	Duration < int, Ratio < 1, 2 > > duration_1(x);

	Duration < int, Ratio < 1, 3 > > duration_2(y);

//  ----------------------------------------------------------------------

	Duration < int, Ratio < 1, 6 > > duration_3 = duration_1 + duration_2;

//  ----------------------------------------------------------------------

	assert(duration_3.x == 7);
}

//////////////////////////////////////////////////////////////////////////////////////////