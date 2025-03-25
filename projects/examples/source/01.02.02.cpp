#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numbers>
#include <string>
#include <vector>

//  using namespace std; // bad

using namespace std::literals;

////////////////////////////////////////////////////////

int main()
{
	auto x = 0;

//  ----------------------------------------------------

	std::cout << "main : enter int : "; std::cin >> x;

	std::cout << "main : x = " << x << '\n';

//  ----------------------------------------------------
	
	assert(std::abs(std::sin(std::numbers::pi)) < 1e-6);

//  ----------------------------------------------------

	auto string = "aaaaa"s;

//  ----------------------------------------------------
	
	assert(string.append("bbbbb").substr(4, 2) == "ab");

//  ----------------------------------------------------

	std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  ----------------------------------------------------
	
	vector.push_back(1);

//  ----------------------------------------------------

	assert(std::size(vector) == 6 && vector.at(0) == 1);

//  ----------------------------------------------------

	std::ranges::sort(vector);
}