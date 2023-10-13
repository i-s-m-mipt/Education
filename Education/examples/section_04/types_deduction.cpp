#include <iostream>

template < typename T >
void f1([[maybe_unused]] T x) {}

template < typename T >
void f2([[maybe_unused]] T & x) {}

template < typename T >
void f3([[maybe_unused]] const T & x) {}

template < typename T >
void f4([[maybe_unused]] T && x) {}

int main()
{
	int           x = 42;
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