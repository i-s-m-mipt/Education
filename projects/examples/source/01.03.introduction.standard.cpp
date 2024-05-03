#include <cmath>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

int main()
{
//	using namespace std; // bad: неудобно в больших проектах

//  ================================================================================================
	
	std::cout << "Enter two integers separated by a space character: ";

	int x{}, y{}; // good: инициализированные нулем переменные

	std::cin >> x >> y; // note: цепочка операторов

	std::cout << "You have entered " << x << " and " << y << std::endl;

//  ================================================================================================

	std::cout << "Enter string with your name: ";

	std::string name; // note: удобно для сложных операций со строками

	std::cin >> name;

	std::cout << "Hello, " << name << std::endl;

//  ================================================================================================

	std::vector < int > vector { 1, 2, 3 }; // note: контейнер по умолчанию

	std::cout << "Vector size is " << std::size(vector) << std::endl;

//  ================================================================================================

	std::cout << "Square root of 4 is " << std::sqrt(4) << std::endl;

	std::swap(x, y); // note: используется в алгоритмах сортировки

	std::cout << "Now x is " << x << " and y is " << y << std::endl;

	return 0;
}