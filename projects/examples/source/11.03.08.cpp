#include <algorithm>
#include <cassert>
#include <forward_list>
#include <functional>
#include <list>
#include <ranges>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int data = 0;
};

////////////////////////////////////////////////////////////////////////////////

template < typename T > class Vector : private std::vector < T >
{
public:

    using std::vector < T > ::begin;

	using std::vector < T > ::  end;

	using std::vector < T > :: size;
};

////////////////////////////////////////////////////////////////////////////////

static_assert( std::ranges::      range < Vector < int > > );

static_assert( std::ranges::sized_range < Vector < int > > );

////////////////////////////////////////////////////////////////////////////////

static_assert(!std::ranges::        sized_range < std::forward_list < int > > );

static_assert( std::ranges::      forward_range < std::forward_list < int > > );

static_assert( std::ranges::bidirectional_range < std::        list < int > > );

static_assert( std::ranges::random_access_range < std::      vector < int > > );

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::vector < Entity > entities = { { 1 }, { 2 }, { 3 }, { 4 }, { 5 } };

//  ------------------------------------------------------------------------

	std::ranges::sort(entities, std::greater(), &Entity::data);

//  ------------------------------------------------------------------------

	assert(std::ranges::is_sorted(entities, std::greater(), &Entity::data));
}