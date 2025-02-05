#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numbers>
#include <string>
#include <vector>

//  using namespace std; // bad

//////////////////////////////////////////////////////////////////////

int main()
{
	{
		std::cout << "main : enter int : "; auto x = 0; std::cin >> x;

		std::cout << "main : x = " << x << '\n';
	}

//  ------------------------------------------------------------------
	
	{
		assert(std::abs(std::sin(std::numbers::pi / 2) - 1.0) < 1e-6);
	}

//  ------------------------------------------------------------------

	{
		std::string string = "aaaaa";

		string.append("bbbbb");
	
		assert(string.contains("aaa") && string.substr(4, 2) == "ab");
	}

//  ------------------------------------------------------------------
	
	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };
	
		vector.push_back(1);

		assert(vector.size() == 6 && vector.front() == vector.back());

		std::ranges::sort(vector);
	}
}