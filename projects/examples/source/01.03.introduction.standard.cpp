#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numbers>
#include <string>
#include <vector>

//  using namespace std; // bad

int main()
{
	std::cout << "Enter 2 integers : "; int x{}, y{}; std::cin >> x >> y;

	std::cout << "Entered integers : " << x << ' ' << y << std::endl;

	assert(std::abs(std::sin(std::numbers::pi / 2.0) - 1.0) < 0.000'001);

	const std::string string = "aaa"; assert(string + "bbb" == "aaabbb");

	std::vector < int > vector { 1, 2, 3, 4, 5 }; vector.push_back(1);

	assert(std::size(vector) == 6 && vector.front() == vector.back());

	std::ranges::sort(vector); assert(std::ranges::is_sorted(vector));

	return 0;
}