#include <algorithm>
#include <cassert>
#include <forward_list>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <ranges>
#include <type_traits>
#include <utility>
#include <vector>

using namespace std::literals;

//  ================================================================================================

struct Entity 
{ 
	int data = 0; 
};

//  ================================================================================================

template < typename T > struct Range : private std::vector < T >
{
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

	std::ranges::transform(std::as_const(vector), std::begin(vector), std::negate());

	std::ranges::sort(vector);

	assert(std::ranges::is_sorted(vector));

	std::vector < Entity > entities({ { 1 }, { 2 }, { 3 } });

	std::ranges::sort(entities, std::ranges::greater(), &Entity::data);

	assert(std::ranges::is_sorted(entities, std::ranges::greater(), &Entity::data));

//  ================================================================================================

	auto lambda_1 = [](auto x){ return x % 2; };
	auto lambda_2 = [](auto x){ return x + 1; };

	for (auto element : std::views::transform(std::views::filter(vector, lambda_1), lambda_2))
	{
		std::cout << element << ' ';
	}

	std::cout << std::endl;

//  ================================================================================================

	for (auto key : std::views::reverse(std::views::keys(map)))
	{
		std::cout << key << ' ';
	}

	std::cout << std::endl;

//  ================================================================================================

	for (auto element : std::views::iota(1) | std::views::take(5) | std::views::drop(1))
	{
		std::cout << element << ' ';
	}

	std::cout << std::endl;

//  ================================================================================================

	for (auto string = "1,2,3,4,5"s; auto substring : std::views::split(string, ','))
	{
		std::cout << std::string(std::cbegin(substring), std::cend(substring)) << ' ';
	}

	std::cout << std::endl;

//  ================================================================================================

	auto lambda = [](){ return std::vector({ 1, 2, 3, 4, 5 }); };

    auto dangling_iterator = std::ranges::max_element(lambda());
	
    static_assert(std::is_same_v < std::ranges::dangling, decltype(dangling_iterator) > );

//	assert(*dangling_iterator == 5); // error
}