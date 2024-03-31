#include <iostream>
#include <utility>

// =================================================================================================

class X {};

inline void g(      X & ) { std::cout << "      X & " << std::endl; }
inline void g(const X & ) { std::cout << "const X & " << std::endl; }
inline void g(      X &&) { std::cout << "      X &&" << std::endl; }

// =================================================================================================

/*
inline void f(      X &  x) { g(          x ); } // bad: multiple overloads for all cases
inline void f(const X &  x) { g(          x ); }
inline void f(      X && x) 
{ 
    g(std::move(x)); // note: local argument x is lvalue, move semantics is not transmitted
} 
*/

// =================================================================================================

template < typename T > inline void f(T && x) // good: forwarding reference, T && or auto &&
{
    g(std::forward < T > (x)); // good: perfect forwarding, maintain fundamental properties
}

// =================================================================================================

template < typename F, typename ... Types > 
[[nodiscard]] inline constexpr decltype(auto) invoke(F && f, Types && ... args) 
{ 
	return f(std::forward < Types > (args)...); // note: see std::invoke
}

// =================================================================================================

int main()
{
	X x; const X cx; // note: objects with different fundamental properties

	f(          x ); // note: f -> g for       X &  x
	f(         cx ); // note: f -> g for const X &  x
	f(std::move(x)); // note: f -> g for       X && x

	return 0;
}