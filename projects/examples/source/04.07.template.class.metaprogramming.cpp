template < int X > struct Factorial // support: cppinsights.io
{
	static constexpr auto value = X * Factorial < X - 1 > ::value;
};

template <> struct Factorial < 0 > 
{ 
	static constexpr auto value = 1;
};

template < int X > constexpr auto factorial_v = Factorial < X > ::value;

////////////////////////////////////////////////////////////////////////////

template < int X, int D > struct Handler
{
	static constexpr auto value = X % D != 0 && Handler < X, D - 1 > ::value;
};

template < int X > struct Handler < X, 2 >
{
	static constexpr auto value = X % 2 != 0;
};

////////////////////////////////////////////////////////////////////////////

template < int X > struct Is_Prime
{
	static constexpr auto value = Handler < X, X / 2 > ::value;
};

template <> struct Is_Prime < 0 > {	static constexpr bool value = 0; };

template <> struct Is_Prime < 1 > { static constexpr bool value = 0; };

template <> struct Is_Prime < 2 > { static constexpr bool value = 1; };

template <> struct Is_Prime < 3 > { static constexpr bool value = 1; };

template < int X > constexpr auto is_prime_v = Is_Prime < X > ::value;

////////////////////////////////////////////////////////////////////////////

int main()
{
	static_assert(factorial_v < 5 > == 120 && is_prime_v < 5 > );
}