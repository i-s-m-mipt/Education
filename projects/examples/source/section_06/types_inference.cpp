#include <iostream>

template < typename T > inline void f1(      T   ) { std::cout << "      T   " << std::endl; }
template < typename T > inline void f2(      T & ) { std::cout << "      T & " << std::endl; }
template < typename T > inline void f3(const T & ) { std::cout << "const T & " << std::endl; }
template < typename T > inline void f4(      T &&) { std::cout << "      T &&" << std::endl; }

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