template < unsigned int X > struct Factorial // support: cppinsights.io
{
	static constexpr auto value = X * Factorial < X - 1 > ::value;
};

template <> struct Factorial < 0 > 
{ 
	static constexpr auto value = 1; 
};

template < unsigned int X > constexpr auto factorial_v = Factorial < X > ::value;

//  ================================================================================================

template < unsigned int X, unsigned int D > struct Helper
{
	static constexpr auto value = X % D != 0 && Helper < X, D - 1 > ::value;
}; 

template < unsigned int X > struct Helper < X, 2 >
{
	static constexpr auto value = X % 2 != 0;
}; 

//  ================================================================================================

template < unsigned int X > struct Is_Prime
{
	static constexpr auto value = Helper < X, X / 2 > ::value;
}; 

template <> struct Is_Prime < 0 > {	static constexpr auto value = false; };
template <> struct Is_Prime < 1 > { static constexpr auto value = false; };
template <> struct Is_Prime < 2 > { static constexpr auto value =  true; };
template <> struct Is_Prime < 3 > { static constexpr auto value =  true; };

template < unsigned int X > constexpr auto is_prime_v = Is_Prime < X > ::value;

//  ================================================================================================

int main()
{
	static_assert(factorial_v < 5 > == 120 && is_prime_v < 5 > );
}