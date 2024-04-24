#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <boost/container_hash/hash.hpp>

// =================================================================================================

[[nodiscard]] inline constexpr std::size_t hash(const std::string & string) noexcept // note: Java hash for strings
{
	std::size_t seed = 0;

	for (const auto element : string)
	{
		(seed *= 31) += static_cast < std::size_t > (element); // note: prime number
	}

	return seed;
}

// =================================================================================================

namespace detail
{
	template < typename T > inline void bind(std::size_t & seed, const T & value) noexcept
	{
		(seed *= 31) += std::hash < T > ()(value); // note: consider ^ instead of +
	}

	template < typename T > inline void hash(std::size_t & seed, const T & value) noexcept
	{
		bind(seed, value);
	}

	template < typename T, typename ... Ts > 

	inline void hash(std::size_t & seed, const T & value, const Ts & ... args) noexcept
	{
		bind(seed, value); hash(seed, args...);
	}

} // namespace detail

template < typename ... Ts > [[nodiscard]] inline std::size_t combined_hash(const Ts & ... args) noexcept
{
	std::size_t seed = 0; detail::hash(seed, args...); return seed;
}

// =================================================================================================

struct S { std::string string_1, string_2; };

[[nodiscard]] inline std::size_t hash_value(const S & s) noexcept
{
	std::size_t seed = 0;

	boost::hash_combine(seed, s.string_1);
	boost::hash_combine(seed, s.string_2);

	return seed;
}

// =================================================================================================

int main()
{
	std::cout << hash("Hello, world!") << std::endl;

	std::cout <<   std::hash < std::string > ()("Hello, world!") << std::endl;
	std::cout << boost::hash < std::string > ()("Hello, world!") << std::endl;

	const S s { "hello", "world" };

	std::cout << combined_hash(s.string_1, s.string_2) << std::endl;

	std::cout << boost::hash < S > ()(s) << std::endl;

	const std::vector < std::string > vector { "hello", "world" };

	std::cout << boost::hash_range(std::cbegin(vector), std::cend(vector)) << std::endl;

	return 0;
}