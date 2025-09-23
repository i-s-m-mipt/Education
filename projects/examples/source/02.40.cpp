///////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <iostream>
#include <span>
#include <string>
#include <vector>

///////////////////////////////////////////////////

void test(int x, int * y, int & z) 
{ 
	++x, ++(*y), ++z;
}

///////////////////////////////////////////////////

void show(int * array, std::size_t size) 
{ 
	std::cout << "show : array = { ";

	for (auto i = 0uz; i < size; ++i)
	{
		std::cout << array[i] << ' ';
	}

	std::cout << "}\n"; 
}

///////////////////////////////////////////////////

void show(std::span < const int > span) 
{ 
	std::cout << "show : vector = { ";

	for (auto i = 0uz; i < std::size(span); ++i)
	{
		std::cout << span[i] << ' ';
	}

	std::cout << "}\n";
}

///////////////////////////////////////////////////

void show(std::string const & string) 
{ 
	std::cout << "show : string = { ";

	for (auto i = 0uz; i < std::size(string); ++i)
	{
		std::cout << string[i] << ' ';
	}

	std::cout << "}\n"; 
}

///////////////////////////////////////////////////

void show(std::vector < int > const & vector) 
{ 
	std::cout << "show : vector = { ";

	for (auto i = 0uz; i < std::size(vector); ++i)
	{
		std::cout << vector[i] << ' ';
	}

	std::cout << "}\n";  
}

///////////////////////////////////////////////////

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

///////////////////////////////////////////////////