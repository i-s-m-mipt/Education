#include <cassert>
#include <concepts>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

//  ================================================================================================

namespace detail
{
	template < typename I > 

	inline constexpr void advance(I & iterator, int distance, std::forward_iterator_tag) noexcept
	{
		if (distance > 0)
		{
			while (distance--) ++iterator;
		}
	}

//  ================================================================================================

	template < typename I > 

	inline constexpr void advance(I & iterator, int distance, std::bidirectional_iterator_tag) noexcept
	{
		if (distance > 0)
		{
			while (distance--) ++iterator;
		}
		else
		{
			while (distance++) --iterator;
		}
	}

//  ================================================================================================

	template < typename I > 

	inline constexpr void advance(I & iterator, int distance, std::random_access_iterator_tag) noexcept
	{
		iterator += distance;
	}

} // namespace detail

//  ================================================================================================

template < typename I > inline constexpr void advance_v1(I & iterator, int distance)
{
    detail::advance(iterator, distance, typename std::iterator_traits < I > ::iterator_category());
}

//  ================================================================================================

template < std::forward_iterator I > 

inline constexpr void advance_v2(I & iterator, int distance) noexcept
{
	if (distance > 0)
	{
		while (distance--) ++iterator;
	}
}

//  ================================================================================================

template < std::bidirectional_iterator I > 

inline constexpr void advance_v2(I & iterator, int distance) noexcept
{
	if (distance > 0)
	{
		while (distance--) ++iterator;
	}
	else
	{
		while (distance++) --iterator;
	}
}

//  ================================================================================================

template < std::random_access_iterator I >
 
inline constexpr void advance_v2(I & iterator, int distance) noexcept
{
	iterator += distance;
}

//  ================================================================================================

int main()
{
	std::vector vector { 1, 2, 3, 4, 5 };

	using category_t = typename decltype(vector)::iterator::iterator_category;

	static_assert(std::is_same_v < category_t, std::random_access_iterator_tag > );

	using value_type = std::iterator_traits < decltype(vector)::iterator > ::value_type;

	static_assert(std::is_same_v < value_type, int > );

//  ================================================================================================

	auto begin = vector.begin(); // support: std::begin, std::end

	std::advance(begin, 1);

	advance_v1(begin, +2);
	advance_v2(begin, -2);

	assert(*begin == 2);

	assert(*std::next(vector.begin(), 2) == 3);
	assert(*std::prev(vector.end  (), 2) == 4);

//  ================================================================================================

	for (auto iterator = vector.begin(); iterator != vector.end(); ++iterator)
	{
		std::cout << *iterator << ' ';
	}

	std::cout << std::endl;

//  ================================================================================================

	for (auto iterator = vector.rbegin(); iterator != vector.rend(); ++iterator)
	{
		std::cout << *iterator << ' ';
	}

	std::cout << std::endl;

//  ================================================================================================

	vector.resize(100);

	std::cout << *begin << std::endl; // support: -D_GLIBCXX_DEBUG

	return 0;
}