#ifndef PROJECT_HEADER_HPP
#define PROJECT_HEADER_HPP

#pragma once

#include <boost/asio.hpp>

//  ================================================================================================

void f();

void g();

/*
void h() { std::cout << "h from header" << std::endl; } // error
*/

//  ================================================================================================

void test_macros();

//  ================================================================================================

class C { public: void print() const; };

//  ================================================================================================

template < typename T1, typename T2 > [[nodiscard]] inline constexpr auto max(T1 x, T2 y)
{
	return (x < y ? y : x);
}

//  ================================================================================================

namespace education
{
	namespace examples
	{
		void print();

		class X {};

		void function_with_ADL(X);

	} // namespace examples

} // namespace education

//  ================================================================================================

namespace constants
{
//	const double old_pi = 3.14; // bad

	constexpr double pi = 3.14;

} // namespace constants

#endif // #ifndef PROJECT_HEADER_HPP