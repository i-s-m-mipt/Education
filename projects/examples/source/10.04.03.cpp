#include <iterator>
#include <tuple>
#include <vector>

#include <boost/container_hash/hash.hpp>

//////////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > auto hash(T x, Ts ... xs)
{
	auto seed = std::hash < T > ()(x);

	if constexpr (sizeof...(xs) > 0)
	{
		seed += hash(xs...) * 31;
	}
	
	return seed;
}

//////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int x = 0, y = 0;
};

//////////////////////////////////////////////////////////////////////////

auto hash_value(const Entity & entity)
{
	auto seed = 0uz;

//  ------------------------------------

	boost::hash_combine(seed, entity.x);
	
	boost::hash_combine(seed, entity.y);

//  ------------------------------------

	return seed;
}

//////////////////////////////////////////////////////////////////////////

int main()
{
    std::ignore = hash(1, 2, 3);

//  ----------------------------------------------------------------------

	std::ignore = boost::hash < Entity > ()(Entity(1, 1));

//  ----------------------------------------------------------------------

	std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  ----------------------------------------------------------------------

	std::ignore = boost::hash_range(std::begin(vector), std::end(vector));
}