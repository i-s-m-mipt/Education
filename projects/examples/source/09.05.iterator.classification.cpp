#include <cassert>
#include <concepts>
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
	using category_1_t = std::vector < int > ::iterator::iterator_category;

	static_assert(std::is_same_v < category_1_t, std::random_access_iterator_tag > );

//  ---------------------------------------------------------------------------------

	std::vector < int > vector({ 1, 2, 3, 4, 5 });

//  ---------------------------------------------------------------------------------

	auto begin = vector.begin();

	std::advance(begin, 1);

	assert(*begin == 2);

	assert(*std::next(vector.begin(), 1) == 2);
	assert(*std::prev(vector.end  (), 1) == 5);

//  ---------------------------------------------------------------------------------

	for (auto iterator = vector.  begin(); iterator != vector.  end(); ++iterator);
	for (auto iterator = vector. cbegin(); iterator != vector. cend(); ++iterator);
	for (auto iterator = vector. rbegin(); iterator != vector. rend(); ++iterator);
	for (auto iterator = vector.crbegin(); iterator != vector.crend(); ++iterator);

//  ---------------------------------------------------------------------------------

	vector.resize(1'000);

	[[maybe_unused]] auto x = *begin; // support: -D_GLIBCXX_DEBUG
}