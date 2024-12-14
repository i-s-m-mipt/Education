#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <boost/container_hash/hash.hpp>

//  ================================================================================================

auto hash_v1(const std::string & string)
{
	auto seed = 0uz;

	for (auto element : string) 
	{
		(seed *= 31) += static_cast < std::size_t > (element);
	}

	return seed;
}

//  ================================================================================================

template < typename T, typename ... Ts > auto hash_v2(T arg, Ts ... args)
{
	auto seed = std::hash < T > ()(arg); 

	if constexpr (sizeof...(args) > 0)
	{
		seed += hash_v2(args...) * 31;
	}
	
	return seed;
}

//  ================================================================================================

struct Entity 
{ 
	int data_1 = 0; 
	int data_2 = 0; 
};

//  ================================================================================================

auto hash_value(const Entity & entity)
{
	auto seed = 0uz;

	boost::hash_combine(seed, entity.data_1);
	boost::hash_combine(seed, entity.data_2);

	return seed;
}

//  ================================================================================================

int main()
{
	std::cout << hash_v1("aaaaa") << '\n';

	std::cout << std::hash < std::string > ()("aaaaa") << '\n';

//  ================================================================================================

	Entity entity(1, 1);

	std::cout << hash_v2(entity.data_1, entity.data_2) << '\n';

	std::cout << boost::hash < Entity > ()(entity) << '\n';

//  ================================================================================================

	std::vector < int > vector { 1, 2, 3, 4, 5 };

	std::cout << boost::hash_range(std::cbegin(vector), std::cend(vector)) << '\n';
}