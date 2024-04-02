#include <cassert>
#include <concepts>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

// =================================================================================================

namespace detail
{
	template < typename I > inline constexpr void advance(I & iterator, int n, std::      forward_iterator_tag) noexcept
	{
		if (n > 0)
		{
			while (n--) ++iterator;
		}
	}

	template < typename I > inline constexpr void advance(I & iterator, int n, std::bidirectional_iterator_tag) noexcept
	{
		if (n > 0)
		{
			while (n--) ++iterator;
		}
		else
		{
			while (n++) --iterator;
		}
	}

	template < typename I > inline constexpr void advance(I & iterator, int n, std::random_access_iterator_tag) noexcept
	{
		iterator += n;
	}

} // namespace detail

// =================================================================================================

template < typename I > inline constexpr void advance_v1(I & iterator, int n)
{
    detail::advance(iterator, n, typename std::iterator_traits < I > ::iterator_category());
}

// =================================================================================================

template < std::      forward_iterator I > inline constexpr void advance_v2(I & iterator, int n) noexcept
{
	if (n > 0)
	{
		while (n--) ++iterator;
	}
}

template < std::bidirectional_iterator I > inline constexpr void advance_v2(I & iterator, int n) noexcept
{
	if (n > 0)
	{
		while (n--) ++iterator;
	}
	else
	{
		while (n++) --iterator;
	}
}

template < std::random_access_iterator I > inline constexpr void advance_v2(I & iterator, int n) noexcept
{
	iterator += n;
}

// =================================================================================================

int main()
{
	const std::vector vector = { 1, 2, 3, 4, 5 };

	using category_t = typename decltype(vector)::iterator::iterator_category;

	static_assert(std::is_same_v < category_t, std::random_access_iterator_tag > );

	using value_type = std::iterator_traits < decltype(vector)::iterator > ::value_type;

	static_assert(std::is_same_v < value_type, int > );

	auto begin = vector.begin(); // note: copy of begin iterator, consider std::begin

	std::advance(begin, 1); // good: better than += or -= in generic programming

	advance_v1(begin, +2);
	advance_v2(begin, -2); // note modern compact implementation based on concepts

	assert(*begin == 2);

	assert(*std::next(vector.begin(), 2) == 3); // good: better than + in generic programming
	assert(*std::prev(vector.end  (), 2) == 4); // good: better than - in generic programming

	for (auto iterator = vector.begin(); iterator != vector.end(); ++iterator) // note: consider std::end
	{
		std::cout << *iterator << ' ';
	}

	std::cout << std::endl;

	for (auto iterator = vector.rbegin(); iterator != vector.rend(); ++iterator) // note: reverse iterators
	{
		std::cout << *iterator << ' ';
	}

	std::cout << std::endl;

	return 0;
}