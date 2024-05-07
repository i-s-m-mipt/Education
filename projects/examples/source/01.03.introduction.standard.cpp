#include <cmath>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

int main()
{
//	using namespace std; // bad: порождает конфликты имен в проектах с несколькими библиотеками

//  ================================================================================================
	
	std::cout << "Enter 2 numbers separated by a space: "; int x{}, y{}; std::cin >> x >> y;

	std::cout << "You have entered " << x << " and " << y << std::endl; 

//  ================================================================================================

	std::cout << "Enter string with your name: "; std::string name; std::cin >> name;

	std::cout << "Hello, " + name << std::endl; 

//  ================================================================================================

	std::vector < int > vector { 1, 2, 3 };

	std::cout << "Vector size is " << std::size(vector) << std::endl;

//  ================================================================================================

	std::cout << "Square root of 4 is " << std::sqrt(4) << std::endl;

	std::swap(x, y); // support: алгоритмы сортировки

	std::cout << "Now x is " << x << " and y is " << y << std::endl;

	return 0;
}