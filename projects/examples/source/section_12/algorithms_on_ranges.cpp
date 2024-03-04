#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <ranges>
#include <utility>
#include <vector>

struct Human
{
	double height{};
	double weight{};

}; // struct Human

int main()
{
	std::vector < int > vector = { 0, 1, 2, 3, 4 };

	for (auto && x : vector) ++x; // note: range-based for

	std::map < int, int > map = { { 1, 10 }, { 2, 20 }, { 3, 30 } };

	for (auto [key, value] : map) // note: structured binding
	{
		std::cout << key << ", " << value << std::endl;
	}

	int array[] = { 1, 2, 3, 4, 5 }; // note: consider as range

	for (auto x : array) std::cout << x << ' ';

	std::cout << std::endl;

	for (auto x : std::views::transform(std::views::filter(vector,
		[](auto x){ return (x % 2); }),
		[](auto x){ return (x + 1); })) // note: funcional syntax
	{
		std::cout << x << ' '; // note: outputs 2 4 6
	}

	std::cout << std::endl;

	std::ranges::transform(std::as_const(vector), std::begin(vector), std::negate());

	std::ranges::sort(vector); // good: instead of iterators

	std::vector < Human > humans = 
	{ 
		{ 175.0, 80.0 }, 
		{ 180.0, 85.0 }, 
		{ 185.0, 90.0 } 
	};

	std::ranges::sort(humans, std::ranges::greater(), &Human::weight);

	for (auto key : std::views::reverse(std::views::keys(map)))
	{
		std::cout << key << ' '; // note: outputs 3 2 1
	}

	std::cout << std::endl;

	for (auto x : std::views::iota(1) | std::views::take(5)) // note: syntax sugar
	{
		std::cout << x << ' '; // note: outputs 1 2 3 4 5
	}		

	return 0;
}