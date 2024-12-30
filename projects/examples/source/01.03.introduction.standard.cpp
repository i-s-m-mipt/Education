#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numbers>
#include <string>
#include <vector>

//  using namespace std; // bad

using namespace std::literals;

////////////////////////////////////////////////////////////////////////

int main()
{
	std::cout << "main : enter 2 ints : "; int x, y; std::cin >> x >> y;

	std::cout << "main : x = " << x << " y = " << y << '\n';

	static_assert(std::abs(std::sin(std::numbers::pi) - 0.0) < 1e-6);

	auto string = "aaaaa"s; 
	
	assert(string.substr(1, 3).contains('a'));

	std::vector < int > vector({ 1, 2, 3, 4, 5 }); 
	
	vector.push_back(1);

	assert(std::size(vector) == 6 && vector.front() == vector.back());

	std::ranges::sort(vector); 
	
	assert(std::ranges::is_sorted(vector));
}