#include <iostream>
#include <utility>

//  ================================================================================================

class C {};

inline void g(      C & ) { std::cout << "g(      C & )" << std::endl; }
inline void g(const C & ) { std::cout << "g(const C & )" << std::endl; }
inline void g(      C &&) { std::cout << "g(      C &&)" << std::endl; }

//  ================================================================================================

/*
inline void f(      C &  c) { g(c); } // bad
inline void f(const C &  c) { g(c); }
inline void f(      C && c) 
{ 
    g(std::move(c));
} 
*/

//  ================================================================================================

template < typename T > inline void f(T && c) { g(std::forward < T > (c)); }

//  ================================================================================================

template < typename F, typename ... Ts > 

[[nodiscard]] inline constexpr decltype(auto) invoke(F && f, Ts && ... args) 
{ 
	return f(std::forward < Ts > (args)...);
}

//  ================================================================================================

int main()
{
	C c1; const C c2;

	f(          c1 );
	f(          c2 );
	f(std::move(c1));

	return 0;
}