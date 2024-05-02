#include <iostream>

//  ================================================================================================

template < typename T > inline void f1(      T   ) { std::cout << "f1(      T   )" << std::endl; }
template < typename T > inline void f2(      T & ) { std::cout << "f2(      T & )" << std::endl; }
template < typename T > inline void f3(const T & ) { std::cout << "f3(const T & )" << std::endl; }
template < typename T > inline void f4(      T &&) { std::cout << "f4(      T &&)" << std::endl; }

//  ================================================================================================

int main()
{
	int    vx = 42; const int    cvx = 42;
	int &  lx = vx; const int &  clx = vx; // note: lvalue-references as lvalues
	int && rx = 42; const int && crx = 42; // note: rvalue-references as lvalues

//  ================================================================================================

	f1( vx); // note: T ->       int
	f1(cvx); // note: T ->       int
	f1( lx); // note: T ->       int
	f1(clx); // note: T ->       int
	f1( rx); // note: T ->       int
	f1(crx); // note: T ->       int

//  ================================================================================================

	f2( vx); // note: T ->       int
	f2(cvx); // note: T -> const int
	f2( lx); // note: T ->       int
	f2(clx); // note: T -> const int
	f2( rx); // note: T ->       int
	f2(crx); // note: T -> const int

//  ================================================================================================

	f3( vx); // note: T ->       int
	f3(cvx); // note: T ->       int
	f3( lx); // note: T ->       int
	f3(clx); // note: T ->       int
	f3( rx); // note: T ->       int
	f3(crx); // note: T ->       int

//  ================================================================================================

	f4( vx); // note: T ->       int &
	f4(cvx); // note: T -> const int &
	f4( lx); // note: T ->       int &
	f4(clx); // note: T -> const int &
	f4( rx); // note: T ->       int &
	f4(crx); // note: T -> const int &

	f4( 42); // note: T ->       int

	return 0;
}