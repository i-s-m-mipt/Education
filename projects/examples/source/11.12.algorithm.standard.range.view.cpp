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

//  ================================================================================================

struct Human { double height{}, weight{}; };

//  ================================================================================================

template < typename T > class Range : private std::vector < T >
{
public:

    using std::vector < T > ::begin;
	using std::vector < T > ::  end;
	using std::vector < T > :: size;

}; // template < typename T > class Range : private std::vector < T >

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
	std::vector < int > vector { 0, 1, 2, 3, 4 };

	for (auto && element : vector) ++element; // support: cppinsights.io

//  ================================================================================================

	const std::map < int, int > map { { 1, 10 }, { 2, 20 }, { 3, 30 } };

	for (const auto [key, value] : map) // support: cppinsights.io
	{
		std::cout << key << ", " << value << std::endl;
	}

//  ================================================================================================

	constexpr int array[]{ 1, 2, 3, 4, 5 };

	for (const auto element : array) std::cout << element << ' ';

	std::cout << std::endl;

//  ================================================================================================

	assert(*std::ranges::begin(vector) == 1 && std::ranges::size(vector) == 5);

	std::ranges::transform(std::as_const(vector), std::begin(vector), std::negate());

	std::ranges::sort(vector);

	std::vector < Human > humans = 
	{ 
		{ 175.0, 80.0 }, 
		{ 180.0, 85.0 }, 
		{ 185.0, 90.0 } 
	};

	std::ranges::sort(humans, std::ranges::greater(), &Human::weight);

//  ================================================================================================

	for (const auto x : std::views::transform(std::views::filter(vector,

		[](auto x) constexpr noexcept { return (x % 2); }),
		[](auto x) constexpr noexcept { return (x + 1); }))
	{
		std::cout << x << ' ';
	}

	std::cout << std::endl;

//  ================================================================================================

	for (const auto key : std::views::reverse(std::views::keys(map)))
	{
		std::cout << key << ' ';
	}

	std::cout << std::endl;

//  ================================================================================================

	for (const auto x : std::views::iota(1) | std::views::take(5))
	{
		std::cout << x << ' ';
	}

	std::cout << std::endl;

//  ================================================================================================
 
    for (const auto x : std::views::iota     (1, 6)
                      | std::views::filter   ([](auto x) constexpr noexcept { return (x % 2); })
                      | std::views::transform([](auto x) constexpr noexcept { return (x * x); })
				      | std::views::drop     (1))
	{
		std::cout << x << ' ';
	}

    std::cout << std::endl;

//  ================================================================================================

	for (const std::string data = "1,2,3,4,5"; auto x : std::views::split(data, ','))
	{
		std::cout << std::string(std::cbegin(x), std::cend(x)) << ' ';
	}

	std::cout << std::endl;

//  ================================================================================================

	constexpr auto lambda = []() constexpr { return std::vector({ 1, 2, 3, 4, 5 }); };

    constexpr auto dangling_iterator = std::ranges::max_element(lambda());
	
    static_assert(std::is_same_v < const std::ranges::dangling, decltype(dangling_iterator) > );

//	assert(*dangling_iterator == 5); // error

	return 0;
}