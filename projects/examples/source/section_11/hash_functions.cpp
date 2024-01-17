#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include <boost/container_hash/hash.hpp>

auto hash(const std::string & string) // note: sequential hash function for strings
{
	std::size_t seed = 0;

	for (std::size_t i = 0; i < std::size(string); ++i)
	{
		(seed *= 31) += static_cast < std::size_t > (string[i]); // note: prime number
	}

	return seed;
}

template < typename T > void bind(std::size_t & seed, const T & value) noexcept
{
	(seed *= 31) += std::hash < T > ()(value); // note: consider ^ instead of +
}

template < typename T > void hash(std::size_t & seed, const T & value) noexcept
{
	bind(seed, value);
}

template < typename T, typename ... Types > 
void hash(std::size_t & seed, const T & value, const Types & ... args) noexcept
{
	bind(seed, value); hash(seed, args...);
}

template < typename ... Types > std::size_t combined_hash(const Types & ... args) noexcept
{
	std::size_t seed = 0; 
	
	hash(seed, args...); 
	
	return seed;
}

struct S
{
	std::string string_1;
	std::string string_2;
	std::string string_3;

}; // struct S

std::size_t hash_value(const S & s)
{
	std::size_t seed = 0;

	boost::hash_combine(seed, s.string_1);
	boost::hash_combine(seed, s.string_2);
	boost::hash_combine(seed, s.string_3);

	return seed;
}

int main()
{
	std::cout << hash("hello, world!") << std::endl;

	std::cout <<   std::hash < std::string > ()("hello, world!") << std::endl;
	std::cout << boost::hash < std::string > ()("hello, world!") << std::endl;

	S s = { "hello", "hashing", "world" };

	std::cout << combined_hash(s.string_1, s.string_2, s.string_3) << std::endl;

	std::cout << boost::hash < S > ()(s) << std::endl;

	std::vector < std::string > vector({ "hello", "hashing", "world" });

	std::cout << boost::hash_range(std::begin(vector), std::end(vector)) << std::endl;

	return 0;
}