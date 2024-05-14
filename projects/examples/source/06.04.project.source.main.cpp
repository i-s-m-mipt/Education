#include "06.06.project.header.precompiled.hpp"

#include <iostream>

#include "06.02.project.header.hpp"

/*
import math;
*/

//  ================================================================================================

/*
void f() { std::cout << "f from source.main" << std::endl; } // error
*/

inline void print() { std::cout << "::print" << std::endl; }

//  ================================================================================================

int main()
{
	f();

//	g(); // error

//  ================================================================================================

	[[maybe_unused]] extern       int global_x1;
	[[maybe_unused]] extern       int global_x2;

	[[maybe_unused]] extern const int global_y1;
	[[maybe_unused]] extern const int global_y2;

	std::cout << global_x1 << std::endl;
//	std::cout << global_x2 << std::endl; // error

//	std::cout << global_y1 << std::endl; // error
	std::cout << global_y2 << std::endl;

//  ================================================================================================

	test_macros();

//  ================================================================================================

	education::examples::print();

	namespace ee = education::examples;

	ee::print();

	  ::print();

	function_with_ADL(ee::X());

//	using namespace std; // bad

	using std::cout;

//  ================================================================================================

//	hello_module(); hello_submodule();

//	std::cout << invoke(math::f, 0.0) << std::endl;
//	std::cout << invoke(math::g, 0.0) << std::endl;
//	std::cout << invoke(math::h, 0.0) << std::endl;

	return EXIT_SUCCESS;
}