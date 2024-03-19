#ifndef PROJECT_HEADER_HPP
#define PROJECT_HEADER_HPP // note: standard header file guard

#pragma once // good: new style non-standard header file guard

//#pragma warning(push) // note: disable warnings for one header file

//#pragma warning(disable: 4715) 
//#pragma warning(disable: 4459)

#include <boost/asio.hpp> // note: external library header file

//#pragma warning(pop)

// =============================================================================

void f(); // good: forward declaration in header file

void g(); // note: forward declaration only

/*
void h() // error: one definition rule violation
{
	std::cout << "h from header" << std::endl;
}
*/

void test_macros();

// =============================================================================

class C { public: void print() const; }; // good: class definition in header file

template < typename T1, typename T2 > [[nodiscard]] inline constexpr auto max(T1 x, T2 y)
{
	return (x < y ? y : x); // good: template definition in header file, no separation
}

// =============================================================================

namespace education
{
	namespace examples // note: nested namespace
	{
		void print();

		class X {};

		void function_with_ADL(X);

	} // namespace examples

} // namespace education

namespace constants
{
//	const double old_pi = 3.14; // bad: internal linkage, multiple copies

	constexpr double pi = 3.14; // good: one definition, inline constant

} // namespace constants

#endif // #ifndef PROJECT_HEADER_HPP