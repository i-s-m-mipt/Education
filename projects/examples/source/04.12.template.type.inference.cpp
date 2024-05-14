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
	int &  lx = vx; const int &  clx = vx; 
	int && rx = 42; const int && crx = 42;

//  ================================================================================================

	f1( vx); // detail:       int
	f1(cvx); // detail:       int
	f1( lx); // detail:       int
	f1(clx); // detail:       int
	f1( rx); // detail:       int
	f1(crx); // detail:       int

//  ================================================================================================

	f2( vx); // detail:       int
	f2(cvx); // detail: const int
	f2( lx); // detail:       int
	f2(clx); // detail: const int
	f2( rx); // detail:       int
	f2(crx); // detail: const int

//  ================================================================================================

	f3( vx); // detail:       int
	f3(cvx); // detail:       int
	f3( lx); // detail:       int
	f3(clx); // detail:       int
	f3( rx); // detail:       int
	f3(crx); // detail:       int

//  ================================================================================================

	f4( vx); // detail:       int &
	f4(cvx); // detail: const int &
	f4( lx); // detail:       int &
	f4(clx); // detail: const int &
	f4( rx); // detail:       int &
	f4(crx); // detail: const int &

	f4( 42); // detail:       int

	return 0;
}