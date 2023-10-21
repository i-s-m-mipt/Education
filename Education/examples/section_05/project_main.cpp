#include <iostream> // note: standard library header file

#include "project_header.hpp" // note: user defined header file

import math;

/*
void f() // error: multiple defined symbol
{
	std::cout << "f from main" << std::endl;
}
*/

void print()
{
	std::cout << "print from global" << std::endl;
}

int main()
{
	f();

//	g(); // error: unresolved external symbol

	extern int global_x1; // note: global variable forward declaration
	extern int global_x2; // note: global variable forward declaration

	std::cout << global_x1 << std::endl;
//	std::cout << global_x2 << std::endl; // error: unresolved external symbol

	extern const int global_y1; // note: global constant forward declaration
	extern const int global_y2; // note: global constant forward declaration

//	std::cout << global_y1 << std::endl; // error: unresolved external symbol
	std::cout << global_y2 << std::endl;

	test_macros();

	C().print();

	education::examples::print();

	namespace ee = education::examples; // note: namespace alias

	ee::print();

	::print(); // note: print from global scope

//	using namespace std; // bad: dangerous in big projects

	using std::cout; // note: possible in local scope

	hello_module();

	std::cout << call(math::f, 0.0) << std::endl; // note: no problems here
	std::cout << call(math::g, 0.0) << std::endl; // note: no problems here
	std::cout << call(math::h, 0.0) << std::endl; // note: no problems here

	return 0;
}