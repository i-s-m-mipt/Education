////////////////////////////////////////////////////////////////

// chapter : Introduction and Environment

////////////////////////////////////////////////////////////////

// content : Standard Template Library (STL)
//
// content : Using Libraries
//
// content : Directive #include
//
// content : Namespace std
//
// content : Declaration using
//
// content : Function main
//
// content : Naming Conventions
//
// content : Comments and Documentation
//
// content : Service Doxygen

////////////////////////////////////////////////////////////////

// support : https://www.doxygen.nl

////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <iostream>
#include <numbers>
#include <print>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////

// using namespace std; // bad

////////////////////////////////////////////////////////////////

int main()
{
	int x = 0;

//  ------------------------------------------------------------

	std::print("main : enter int x : "); std::cin >> x;

//  ------------------------------------------------------------

	std::print("main : x = {}\n", x);

//  ------------------------------------------------------------

	assert(std::abs(std::sin(std::numbers::pi / 2) - 1) < 1e-6);

//  ------------------------------------------------------------

	std::string string = "aaaaa";

//  ------------------------------------------------------------

	std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  ------------------------------------------------------------

	vector.push_back(1);

//  ------------------------------------------------------------

	assert(vector.size() == 6 && vector[5] == vector[0]);

//  ------------------------------------------------------------

	return 0;
}

////////////////////////////////////////////////////////////////