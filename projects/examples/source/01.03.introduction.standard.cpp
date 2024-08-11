#include <cmath>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

/*
using namespace std; // bad
*/

int main()
{	
	std::cout << "Enter two integers: "; int x{}, y{}; std::cin >> x >> y;

	std::cout << "You have entered integers " << x << " and " << y << std::endl;

//  ================================================================================================

	std::cout << "Enter string: "; std::string string; std::cin >> string;

	std::cout << "You have entered string " + string << std::endl;

//  ================================================================================================

	std::vector < int > vector { 1, 2, 3, 4, 5 }; vector.push_back(42);

	std::cout << "Vector has " << std::size(vector) << " elements" << std::endl;

	std::cout << "|x| ^ 0.5 = " << std::sqrt(std::abs(x)) << std::endl;

	return 0;
}