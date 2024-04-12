#include <iostream>
#include <utility>

// =================================================================================================

class C {};

inline void g(      C & ) { std::cout << "g(      C & )" << std::endl; }
inline void g(const C & ) { std::cout << "g(const C & )" << std::endl; }
inline void g(      C &&) { std::cout << "g(      C &&)" << std::endl; }

// =================================================================================================

/*
inline void f(      C &  c) { g(c); } // bad: multiple overloads for all cases
inline void f(const C &  c) { g(c); }
inline void f(      C && c) 
{ 
    g(std::move(c)); // note: local argument c is lvalue, move semantics is not transmitted
} 
*/

// =================================================================================================

template < typename T > inline void f(T && c) // good: forwarding reference, T && or auto &&
{
    g(std::forward < T > (c)); // good: perfect forwarding, maintain fundamental properties
}

template < typename F, typename ... Ts > 
[[nodiscard]] inline constexpr decltype(auto) invoke(F && f, Ts && ... args) 
{ 
	return f(std::forward < Ts > (args)...); // note: see std::invoke
}

// =================================================================================================

int main()
{
	C c; const C cc; // note: objects with different fundamental properties

	f(          c ); // note: f -> g for       C &  c
	f(         cc ); // note: f -> g for const C &  c
	f(std::move(c)); // note: f -> g for       C && c

	return 0;
}