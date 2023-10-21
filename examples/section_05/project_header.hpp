#ifndef PROJECT_HEADER_HPP
#define PROJECT_HEADER_HPP // note: standard header file guard

#pragma once // good: new style non-standard header file guard

void f(); // good: forward declaration in header file

void g(); // note: forward declaration only

/*
void h() // error: one definition rule violation
{
	std::cout << "h from header" << std::endl;
}
*/

void test_macros();

class C // good: class definition in header file
{
public:

	void print() const;

}; // class C

template < typename T1, typename T2 >
auto max(T1 x, T2 y) // note: template definition only in header file
{
	return (x < y ? y : x);
}

namespace education
{
	namespace examples // note: nested namespace
	{
		void print();

	} // namespace examples

} // namespace education

namespace constants
{
//	const double old_pi = 3.14; // bad: internal linkage, multiple copies

	inline const double pi = 3.14; // good: one definition

} // namespace constants

#endif // #ifndef PROJECT_HEADER_HPP