#include <algorithm>
#include <cassert>
#include <concepts>
#include <forward_list>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <ranges>
#include <string>
#include <type_traits>
#include <vector>

using namespace std::literals;

//////////////////////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int data = 0; 
};

//////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Range : private std::vector < T >
{
public:

    using std::vector < T > ::begin;

	using std::vector < T > ::  end;

	using std::vector < T > :: size;
};

//////////////////////////////////////////////////////////////////////////////////////////////

static_assert( std::ranges::      range < Range < int > > );

static_assert( std::ranges::sized_range < Range < int > > );

//////////////////////////////////////////////////////////////////////////////////////////////

static_assert(!std::ranges::        sized_range < std::forward_list < int > > );

static_assert( std::ranges::      forward_range < std::forward_list < int > > );

static_assert( std::ranges::bidirectional_range < std::        list < int > > );

static_assert( std::ranges::random_access_range < std::      vector < int > > );

//////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		int array[5]{};

		for (auto x = 0; auto && element : array) // support: cppinsights.io
		{
			element = ++x;
		}
	}

//  ------------------------------------------------------------------------------------------

	{
		std::vector < int > vector(5, 0);

		for (auto x = 0; auto && element : vector)
		{
			element = ++x;
		}
	}	

//  ------------------------------------------------------------------------------------------

	{
		std::map < int, int > map = { { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 }, { 5, 0 } };

		for (auto x = 0; auto && [first, second] : map)
		{
			second = ++x;
		}
	}

//  ------------------------------------------------------------------------------------------

	{
		std::vector < Entity > entities = { { 1 }, { 2 }, { 3 }, { 4 }, { 5 } };

		std::ranges::sort(entities, std::greater(), &Entity::data);

		assert(std::ranges::is_sorted(entities, std::greater(), &Entity::data));
	}

//  ------------------------------------------------------------------------------------------

	{
		for ([[maybe_unused]] auto element : std::ranges::views::iota(1, 5)); 

		std::cout << "main : enter ints and non-int : ";

		for ([[maybe_unused]] auto element : std::views::istream < int > (std::cin));

		auto string = "1,2,3,4,5"s;

		for ([[maybe_unused]] auto element : std::ranges::views::split(string, ','));

		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		auto lambda = [](auto x){ return -x; };

		for ([[maybe_unused]] auto element : std::ranges::views::transform(vector, lambda));
	}

//  ------------------------------------------------------------------------------------------

	{
		auto iterator = std::ranges::max_element
		(
			[](){ return std::vector < int > ({ 1, 2, 3, 4, 5 }); }()
		);
		
		static_assert(std::is_same_v < decltype(iterator), std::ranges::dangling > );

//		assert(*terator == 5); // error
	}
}