#include "06.06.project.header.precompiled.hpp" // note: precompiled header must be first

#include <iostream> // note: standard library header file

#include "06.02.project.header.hpp" // note: user defined header file

//import math; // note: importing module

//  ================================================================================================

/*
void f() // error: multiple defined symbol
{
	std::cout << "f from source.main" << std::endl;
}
*/

inline void print() { std::cout << "::print" << std::endl; }

//  ================================================================================================

int main()
{
	f();

//	g(); // error: unresolved external symbol

//  ================================================================================================

	[[maybe_unused]] extern int global_x1; // note: declaration
	[[maybe_unused]] extern int global_x2; // note: declaration

	std::cout << global_x1 << std::endl;
//	std::cout << global_x2 << std::endl; // error: unresolved external symbol

	[[maybe_unused]] extern const int global_y1; // note: declaration
	[[maybe_unused]] extern const int global_y2; // note: declaration

//	std::cout << global_y1 << std::endl; // error: unresolved external symbol
	std::cout << global_y2 << std::endl;

//  ================================================================================================

	test_macros();

//  ================================================================================================

	education::examples::print();

	namespace ee = education::examples; // note: namespace alias

	ee::print();

	  ::print(); // note: print from global scope

	function_with_ADL(ee::X()); // good: argument-dependent lookup

//	using namespace std; // bad: dangerous in big projects

	using std::cout; // note: possible usage in local scopes

//  ================================================================================================

//	hello_module(); hello_submodule();

//	std::cout << invoke(math::f, 0.0) << std::endl; // note: no problems here
//	std::cout << invoke(math::g, 0.0) << std::endl; // note: no problems here
//	std::cout << invoke(math::h, 0.0) << std::endl; // note: no problems here

	return EXIT_SUCCESS;
}