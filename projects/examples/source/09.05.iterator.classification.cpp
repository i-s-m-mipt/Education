#include <cassert>
#include <concepts>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

//  ================================================================================================

template < typename I > void advance(I & iterator, int distance, std::forward_iterator_tag)
{
	if (distance > 0) 
	{ 
		for (; --distance >= 0; ++iterator); 
	}
}

//  ================================================================================================

template < typename I > void advance(I & iterator, int distance, std::bidirectional_iterator_tag)
{
	if (distance > 0)
	{
		for (; --distance >= 0; ++iterator); 
	}
	else
	{
		for (; ++distance <= 0; --iterator); 
	}
}

//  ================================================================================================

template < typename I > void advance(I & iterator, int distance, std::random_access_iterator_tag)
{
	iterator += distance;
}

//  ================================================================================================

template < typename I > void advance_v1(I & iterator, int distance)
{
    advance(iterator, distance, typename std::iterator_traits < I > ::iterator_category());
}

//  ================================================================================================

template < std::forward_iterator I > void advance_v2(I & iterator, int distance)
{
	if (distance > 0) 
	{ 
		for (; --distance >= 0; ++iterator); 
	}
}

//  ================================================================================================

template < std::bidirectional_iterator I > void advance_v2(I & iterator, int distance)
{
	if (distance > 0)
	{
		for (; --distance >= 0; ++iterator); 
	}
	else
	{
		for (; ++distance <= 0; --iterator); 
	}
}

//  ================================================================================================

template < std::random_access_iterator I > void advance_v2(I & iterator, int distance)
{
	iterator += distance;
}

//  ================================================================================================

int main()
{
	std::vector < int > vector({ 1, 2, 3, 4, 5 });

	using category_t = typename decltype(vector)::iterator::iterator_category;

	static_assert(std::is_same_v < category_t, std::random_access_iterator_tag > );

	using value_type = std::iterator_traits < decltype(vector)::iterator > ::value_type;

	static_assert(std::is_same_v < value_type, int > );

//  ------------------------------------------------------------------------------------------------

	auto begin = vector.begin();

	std::advance(begin, 1);

	assert(*begin == 2);

	assert(*std::next(vector.begin(), 1) == 2);
	assert(*std::prev(vector.end  (), 1) == 5);

//  ------------------------------------------------------------------------------------------------

	for (auto iterator = vector.  begin(); iterator != vector.  end(); ++iterator);
	for (auto iterator = vector. cbegin(); iterator != vector. cend(); ++iterator);
	for (auto iterator = vector. rbegin(); iterator != vector. rend(); ++iterator);
	for (auto iterator = vector.crbegin(); iterator != vector.crend(); ++iterator);

//  ------------------------------------------------------------------------------------------------

	vector.resize(1'000);

	std::cout << "*begin = " << *begin << '\n'; // support: -D_GLIBCXX_DEBUG
}