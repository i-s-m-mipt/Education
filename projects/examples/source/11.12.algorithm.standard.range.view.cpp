#include <algorithm>
#include <cassert>
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
	std::vector < int > vector(5, 0);

	for (int i = 0; auto && element : vector) // support: cppinsights.io
	{
		element = ++i; 
	}

//  ================================================================================================

	std::map < int, int > map { { 1, 10 }, { 2, 20 }, { 3, 30 } };

	for (auto [key, value] : map)
	{
		std::cout << key << ", " << value << std::endl;
	}

//  ================================================================================================

	int array[]{ 1, 2, 3, 4, 5 };

	for (auto element : array) 
	{
		std::cout << element << ' ';
	}

	std::cout << std::endl;

//  ================================================================================================

	assert(*std::ranges::begin(vector) == 1 && std::ranges::size(vector) == 5);

	std::ranges::transform(vector, std::begin(vector), std::negate());

	std::ranges::sort(vector);

	assert(std::ranges::is_sorted(vector));

	std::vector < Entity > entities { { 1 }, { 2 }, { 3 } };

	std::ranges::sort(entities, std::ranges::greater(), &Entity::data);

	assert(std::ranges::is_sorted(entities, std::ranges::greater(), &Entity::data));

//  ================================================================================================

	auto lambda = [](auto x){ return x + 1; };

	for (auto element : std::ranges::views::transform(vector, lambda))
	{
		std::cout << element << ' ';
	}

	std::cout << std::endl;

//  ================================================================================================

	for (auto key : std::ranges::views::reverse(std::ranges::views::keys(map)))
	{
		std::cout << key << ' ';
	}

	std::cout << std::endl;

//  ================================================================================================

	for (auto element : std::ranges::views::iota(1) | 
						std::ranges::views::take(5) | 
						std::ranges::views::drop(1)
		)
	{
		std::cout << element << ' ';
	}

	std::cout << std::endl;

//  ================================================================================================

	for (auto string = "1,2,3,4,5"s; auto substring : std::ranges::views::split(string, ','))
	{
		std::cout << std::string(std::begin(substring), std::end(substring)) << ' ';
	}

	std::cout << std::endl;

//  ================================================================================================

    auto dangling_iterator = std::ranges::max_element
	(
		[](){ return std::vector < int > { 1, 2, 3, 4, 5 }; }()
	);
	
    static_assert(std::is_same_v < std::ranges::dangling, decltype(dangling_iterator) > );

//	assert(*dangling_iterator == 5); // error
}