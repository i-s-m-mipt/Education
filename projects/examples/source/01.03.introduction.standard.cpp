#include <cmath>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

int main()
{
//	using namespace std; // bad: dangerous in big projects, avoid

//  ================================================================================================
	
	std::cout << "Enter two integers separated by a space character: ";

	int x{}, y{}; // good: zero value initialized variables

	std::cin >> x >> y; // note: chaining operators

	std::cout << "You have entered " << x << " and " << y << std::endl;

//  ================================================================================================

	std::cout << "Enter string with your name: ";

	std::string name; // note: comfortable for complex operations

	std::cin >> name;

	std::cout << "Hello, " << name << std::endl;

//  ================================================================================================

	std::vector < int > vector { 1, 2, 3 }; // note: default container

	std::cout << "Vector size is " << std::size(vector) << std::endl;

//  ================================================================================================

	std::cout << "Square root of 4 is " << std::sqrt(4) << std::endl;

	std::swap(x, y); // note: std::swap will be used in sorts

	std::cout << "Now x is " << x << " and y is " << y << std::endl;

	return 0;
}