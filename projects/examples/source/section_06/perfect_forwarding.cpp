#include <iostream>
#include <utility>

// =================================================================================================

class С {};

inline void g(      С & ) { std::cout << "      С & " << std::endl; }
inline void g(const С & ) { std::cout << "const С & " << std::endl; }
inline void g(      С &&) { std::cout << "      С &&" << std::endl; }

// =================================================================================================

/*
inline void f(      С &  с) { g(с); } // bad: multiple overloads for all cases
inline void f(const С &  с) { g(с); }
inline void f(      С && с) 
{ 
    g(std::move(x)); // note: local argument x is lvalue, move semantics is not transmitted
} 
*/

// =================================================================================================

template < typename T > inline void f(T && с) // good: forwarding reference, T && or auto &&
{
    g(std::forward < T > (с)); // good: perfect forwarding, maintain fundamental properties
}

template < typename F, typename ... Types > 
[[nodiscard]] inline constexpr decltype(auto) invoke(F && f, Types && ... args) 
{ 
	return f(std::forward < Types > (args)...); // note: see std::invoke
}

// =================================================================================================

int main()
{
	С с; const С cс; // note: objects with different fundamental properties

	f(          с ); // note: f -> g for       С &  x
	f(         cс ); // note: f -> g for const С &  x
	f(std::move(с)); // note: f -> g for       С && x

	return 0;
}