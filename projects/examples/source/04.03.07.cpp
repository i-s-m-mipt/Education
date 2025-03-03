#include <cassert>

//////////////////////////////////////////////////////////////////////////////////////////

template < int N = 0, int D = 1 > struct Ratio
{
	static constexpr auto num = N;
	
	static constexpr auto den = D;

//  ---------------------------------

	using type = Ratio < num, den > ;
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

template < typename R1, typename R2 > using sum_t = typename Sum < R1, R2 > ::type;

//////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename R = Ratio < 1 > > struct Duration 
{ 
	T data = T();
};

//////////////////////////////////////////////////////////////////////////////////////////

template 
< 
	typename T1, typename R1, 
	
	typename T2, typename R2 
>
constexpr auto operator+(const Duration < T1, R1 > & lhs, const Duration < T2, R2 > & rhs)
{
	using ratio_t = Ratio < 1, sum_t < R1, R2 > ::den > ;

	auto data = 
	(
		lhs.data * ratio_t::den / R1::den * R1::num +

		rhs.data * ratio_t::den / R2::den * R2::num
	);

	return Duration < decltype(data), ratio_t > (data);
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto duration = 
	(
		Duration < int, Ratio < 1, 2 > > (1) +

		Duration < int, Ratio < 1, 3 > > (1)
	);

	assert(duration.data == 5);
}