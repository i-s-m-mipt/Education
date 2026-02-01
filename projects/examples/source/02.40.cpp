/////////////////////////////////////////////////////////////////////

// chapter : Basics of Programming

/////////////////////////////////////////////////////////////////////

// section : Functions and Algorithms

/////////////////////////////////////////////////////////////////////

// content : Passing Arguments by Value, Pointer and Lvalue Reference
//
// content : View std::span
//
// content : String std::string

/////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <print>
#include <span>
#include <string>
#include <vector>

/////////////////////////////////////////////////////////////////////

void test(int x, int * y, int & z) 
{ 
	++x, ++(*y), ++z;
}

/////////////////////////////////////////////////////////////////////

void show(int * array, std::size_t size) 
{ 
	std::print("show : array = {{ ");

	for (auto i = 0uz; i < size; ++i)
	{
		std::print("{} ", array[i]);
	}

	std::print("}}\n"); 
}

/////////////////////////////////////////////////////////////////////

void show(std::span < int const > span) 
{ 
	std::print("show : span = {{ ");

	for (auto i = 0uz; i < std::size(span); ++i)
	{
		std::print("{} ", span[i]);
	}

	std::print("}}\n");
}

/////////////////////////////////////////////////////////////////////

void show(std::string const & string) 
{ 
	std::print("show : string = {{ ");

	for (auto i = 0uz; i < std::size(string); ++i)
	{
		std::print("{} ", string[i]);
	}

	std::print("}}\n");
}

/////////////////////////////////////////////////////////////////////

void show(std::vector < int > const & vector) 
{ 
	std::print("show : vector = {{ ");

	for (auto i = 0uz; i < std::size(vector); ++i)
	{
		std::print("{} ", vector[i]);
	}

	std::print("}}\n"); 
}

/////////////////////////////////////////////////////////////////////

int main()
{
    auto x = 1, y = 2, z = 3;

//  -----------------------------------------------
	
	test(x, &y, z);

//  -----------------------------------------------

	assert(x == 1 && y == 3 && z == 4);

//  -----------------------------------------------

	auto size = 5uz;

//  -----------------------------------------------

	auto array = new int[size]{ 1, 2, 3, 4, 5 };

//  -----------------------------------------------

	show(array, size);
    
//  -----------------------------------------------

	show(std::span < int const > (array, size));

//  -----------------------------------------------

	delete[] array;

//  -----------------------------------------------

	std::string string = "aaaaa";

//  -----------------------------------------------

	show(string);

//  -----------------------------------------------

	std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  -----------------------------------------------

	show(vector);
}

/////////////////////////////////////////////////////////////////////