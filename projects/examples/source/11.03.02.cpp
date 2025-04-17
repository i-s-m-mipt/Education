///////////////////////////////////////////////////////////////////////////////////

#include <forward_list>
#include <list>
#include <ranges>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////

template < typename T > class Vector : private std::vector < T >
{
public :

    using std::vector < T > ::begin;

	using std::vector < T > ::  end;

	using std::vector < T > :: size;
};

///////////////////////////////////////////////////////////////////////////////////

static_assert(std::ranges::      range < Vector < int > > );

static_assert(std::ranges::sized_range < Vector < int > > );

///////////////////////////////////////////////////////////////////////////////////

static_assert(std::ranges::        sized_range < std::forward_list < int > > == 0);

static_assert(std::ranges::      forward_range < std::forward_list < int > > == 1);

static_assert(std::ranges::bidirectional_range < std::        list < int > > == 1);

static_assert(std::ranges::random_access_range < std::      vector < int > > == 1);

///////////////////////////////////////////////////////////////////////////////////

int main() {}

///////////////////////////////////////////////////////////////////////////////////