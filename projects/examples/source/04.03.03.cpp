template < int X > struct Factorial // support : cppinsights.io
{
	static constexpr auto value = X * Factorial < X - 1 > ::value;
};

////////////////////////////////////////////////////////////////////////

template <> struct Factorial < 0 > 
{ 
	static constexpr auto value = 1;
};

////////////////////////////////////////////////////////////////////////

template < int X > constexpr auto factorial_v = Factorial < X > ::value;

////////////////////////////////////////////////////////////////////////

int main()
{
    static_assert(factorial_v < 5 > == 120);
}