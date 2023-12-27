#include <functional>
#include <iostream>
#include <string>

auto hash(const std::string & string) // note: sequential hash function for strings
{
	unsigned int hash = 0;

	for (std::size_t i = 0; i < std::size(string); ++i)
	{
		(hash *= 59) += static_cast < unsigned int > (string[i]); // note: prime number
	}

	return hash;
}

template < typename T > void bind(std::size_t & seed, const T & value) noexcept
{
	seed ^= std::hash < T > ()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2); // note: ^= instead of +=
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

}; // struct S

int main()
{
	std::cout << std::hash < std::string > ()("hello") << std::endl;

	std::cout << hash("hello") << std::endl;

	S s = { "hello", "world" };

	std::cout << combined_hash(s.string_1, s.string_2) << std::endl;

	return 0;
}