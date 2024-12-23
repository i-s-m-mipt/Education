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

//  ================================================================================================

struct Entity 
{ 
	int data = 0; 
};

//  ================================================================================================

template < typename T > class Range : private std::vector < T >
{
public:

    using std::vector < T > ::begin;
	using std::vector < T > ::  end;
	using std::vector < T > :: size;
};

//  ================================================================================================

static_assert(std::ranges::      range < Range < int > > );
static_assert(std::ranges::sized_range < Range < int > > );

static_assert(std::ranges::sized_range < std::forward_list < int > > == false);

static_assert(std::ranges::      forward_range < std::forward_list < int > > );
static_assert(std::ranges::bidirectional_range < std::        list < int > > );
static_assert(std::ranges::random_access_range < std::      vector < int > > );

//  ================================================================================================

int main()
{
	int array[5]{};

	for (auto i = 0; auto && element : array) // support: cppinsights.io
	{
		element = ++i;
	}

//  ------------------------------------------------------------------------------------------------

	std::vector < int > vector(5, 0);

	for (auto i = 0; auto && element : vector)
	{
		element = ++i; 
	}

//  ------------------------------------------------------------------------------------------------

	std::map < int, int > map { { 1, 0 }, { 2, 0 }, { 3, 0 } };

	for (auto i = 0; auto && [key, element] : map)
	{
		element = ++i;
	}

//  ------------------------------------------------------------------------------------------------

	assert(*std::ranges::begin(array) == 1 && std::ranges::size(array) == 5);

	std::ranges::sort(array, std::ranges::greater());

	assert(std::ranges::is_sorted(array, std::ranges::greater()));

//  ------------------------------------------------------------------------------------------------

	std::vector < Entity > entities { { 1 }, { 2 }, { 3 } };

	std::ranges::sort(entities, std::ranges::greater(), &Entity::data);

	assert(std::ranges::is_sorted(entities, std::ranges::greater(), &Entity::data));

//  ------------------------------------------------------------------------------------------------

	for ([[maybe_unused]] auto element : std::ranges::views::iota(1, 5)); 

	for ([[maybe_unused]] auto element : std::ranges::views::iota(1) | std::ranges::views::take(5));

//  ------------------------------------------------------------------------------------------------

	std::cout << "Enter 1 or more integers and 1 non-integer : ";

	for ([[maybe_unused]] auto element : std::views::istream < int > (std::cin));

//  ------------------------------------------------------------------------------------------------

	auto string = "1,2,3,4,5"s;

	for ([[maybe_unused]] auto element : std::ranges::views::split(string, ','));

//  ------------------------------------------------------------------------------------------------

	auto lambda = [](auto x){ return x; };

	for ([[maybe_unused]] auto element : std::ranges::views::transform(vector, lambda));

//  ------------------------------------------------------------------------------------------------

    auto dangling_iterator = std::ranges::max_element
	(
		[](){ return std::vector < int > { 1, 2, 3, 4, 5 }; }()
	);
	
    static_assert(std::is_same_v < std::ranges::dangling, decltype(dangling_iterator) > );

//	assert(*dangling_iterator == 5); // error
}