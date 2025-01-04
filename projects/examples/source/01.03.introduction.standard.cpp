#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numbers>
#include <string>
#include <vector>

//  using namespace std; // bad

////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		std::cout << "main : enter 2 ints : "; int x, y; std::cin >> x >> y;

		std::cout << "main : x = " << x << " y = " << y << '\n';
	}

//  ------------------------------------------------------------------------
	
	{
		assert(std::abs(std::sin(std::numbers::pi / 2) - 1.0) < 1e-6);
	}

//  ------------------------------------------------------------------------

	{
		std::string string = "aaaaa"; 

		string.append("bbbbb");
	
		assert(string.starts_with('a') && string.substr(4, 2) == "ab");
	}

//  ------------------------------------------------------------------------	
	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 }; 
	
		vector.push_back(6);

		assert(std::size(vector) == 6 && std::ranges::is_sorted(vector));
	}
}