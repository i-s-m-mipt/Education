//////////////////////////////////////////////////////////////////////////

#include <functional>
#include <iterator>
#include <string>
#include <tuple>
#include <vector>

//////////////////////////////////////////////////////////////////////////

using namespace std::literals;

//////////////////////////////////////////////////////////////////////////

#include <boost/container_hash/hash.hpp>

//////////////////////////////////////////////////////////////////////////

template < typename T > auto hash(T x, auto ... ys)
{
	auto seed = std::hash < T > ()(x);

	if constexpr (sizeof...(ys) > 0)
	{
		seed += hash(ys...) * 31;
	}
	
	return seed;
}

//////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int x = 0, y = 0;
};

//////////////////////////////////////////////////////////////////////////

auto hash_value(Entity const & entity)
{
	auto seed = 0uz;

	boost::hash_combine(seed, entity.x);
	
	boost::hash_combine(seed, entity.y);

	return seed;
}

//////////////////////////////////////////////////////////////////////////

int main()
{
    std::ignore = hash(1, 2.0, "aaaaa"s);

//  ----------------------------------------------------------------------

	std::ignore = boost::hash < Entity > ()(Entity(1, 1));

//  ----------------------------------------------------------------------

	std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  ----------------------------------------------------------------------

	std::ignore = boost::hash_range(std::begin(vector), std::end(vector));
}

//////////////////////////////////////////////////////////////////////////