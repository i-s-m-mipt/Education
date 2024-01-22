#include <iostream>
#include <iterator>
#include <map>
#include <vector>

int main()
{
	std::vector < int > vector = { 0, 1, 2, 3, 4 };

	for (auto && element : vector) ++element; // note: range-based

	std::map < int, int > map = { { 1, 1 }, { 2, 2 }, { 3, 3 } };

	for (auto [key, value] : map) // note: structured binding
	{
		std::cout << key << ", " << value << std::endl;
	}

	int array[] = { 1, 2, 3, 4, 5 }; // note: also range

	for (auto element : array) std::cout << element << ' ';

	return 0;
}