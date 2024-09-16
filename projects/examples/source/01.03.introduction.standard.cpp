#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

/*
using namespace std; // bad
*/

int main()
{	
	std::cout << "Enter 2 integers: "; int x{}, y{}; std::cin >> x >> y;

	std::cout << "Entered integers: " << x << ' ' << y << std::endl;

	assert(std::abs(std::sin(std::numbers::pi / 2.0) - 1.0) < 0.000001);

	std::vector < int > vector { 1, 2, 3, 4, 5 }; vector.push_back(1);

	std::ranges::sort(vector); assert(std::ranges::is_sorted(vector));

	const std::string s = "01234"; assert(s + "56789" == "0123456789");

	return 0;
}