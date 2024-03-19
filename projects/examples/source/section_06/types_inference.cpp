template < typename T > inline constexpr void f1(      T   ) {}
template < typename T > inline constexpr void f2(      T & ) {}
template < typename T > inline constexpr void f3(const T & ) {}
template < typename T > inline constexpr void f4(      T &&) {}

int main()
{
	      int     x = 42;
	const int    cx =  x;
	const int & rcx = cx;

	f1(  x); // note: T -> int
	f1( cx); // note: T -> int
	f1(rcx); // note: T -> int

	f2(  x); // note: T -> int
	f2( cx); // note: T -> const int
	f2(rcx); // note: T -> const int

	f3(  x); // note: T -> int
	f3( cx); // note: T -> int
	f3(rcx); // note: T -> int

	f4(  x); // note: T -> int &
	f4( cx); // note: T -> const int &
	f4(rcx); // note: T -> const int &
	f4( 42); // note: T -> int

	return 0;
}