////////////////////////////////////////////////////////

// chapter : Introduction and Brief Overview

////////////////////////////////////////////////////////

// section : Standard Library

////////////////////////////////////////////////////////

// content : Standard Library
//
// content : Directive #include
//
// content : Namespace std
//
// content : Declaration using
//
// content : Comments
//
// content : Code Documentation
//
// content : Utility Doxygen

////////////////////////////////////////////////////////

// support : www.doxygen.nl

////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <iostream>
#include <numbers>
#include <print>
#include <string>
#include <vector>

////////////////////////////////////////////////////////

// using namespace std; // bad

////////////////////////////////////////////////////////

int main()
{
	int x = 0;

//  ----------------------------------------------------

	std::print("main : enter int x : "); std::cin >> x;

//  ----------------------------------------------------

	std::print("main : x = {}\n", x);

//  ----------------------------------------------------

	assert(std::abs(std::sin(std::numbers::pi)) < 1e-6);

//  ----------------------------------------------------

	std::string string = "aaaaa";

//  ----------------------------------------------------

	assert(string.append("bbbbb").substr(4, 2) == "ab");

//  ----------------------------------------------------

	std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  ----------------------------------------------------

	vector.push_back(1);

//  ----------------------------------------------------

	assert(std::size(vector) == 6 && vector.at(5) == 1);
}

////////////////////////////////////////////////////////