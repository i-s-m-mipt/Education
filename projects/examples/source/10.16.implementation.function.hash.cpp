#include <cstddef>
#include <functional>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include <boost/container_hash/hash.hpp>

//////////////////////////////////////////////////////////////////////////////

auto hash_v1(const std::string & string)
{
	auto result = 0uz;

	for (auto element : string) 
	{
		(result *= 31) += element;
	}

	return result;
}

//////////////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > auto hash_v2(T x, Ts ... xs)
{
	auto result = std::hash < T > ()(x); 

	if constexpr (sizeof...(xs) > 0)
	{
		result += hash_v2(xs...) * 31;
	}
	
	return result;
}

//////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int data_1 = 0, data_2 = 0; 
};

//////////////////////////////////////////////////////////////////////////////

auto hash_value(const Entity & entity)
{
	auto result = 0uz;

	boost::hash_combine(result, entity.data_1);
	
	boost::hash_combine(result, entity.data_2);

	return result;
}

//////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		auto string = "aaaaa";

		std::ignore = hash_v1(string);

		std::ignore = std::hash < std::string > ()(string);
	}
	
//  --------------------------------------------------------------------------

	{
		Entity entity(1, 1);

		std::ignore = hash_v2(entity.data_1, entity.data_2);

		std::ignore = boost::hash < Entity > ()(entity);
	}

//  --------------------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		std::ignore = boost::hash_range(std::begin(vector), std::end(vector));
	}
}