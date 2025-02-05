#include <cassert>
#include <concepts>
#include <forward_list>
#include <iterator>
#include <list>
#include <type_traits>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename I > void advance(I & iterator, int offset, std::forward_iterator_tag)
{
	if (offset > 0) 
	{
		while (--offset >= 0)
		{
			++iterator;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename I > void advance(I & iterator, int offset, std::bidirectional_iterator_tag)
{
	if (offset > 0)
	{
		while (--offset >= 0)
		{
			++iterator;
		} 
	}
	else
	{
		while (++offset <= 0)
		{
			--iterator;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename I > void advance(I & iterator, int offset, std::random_access_iterator_tag)
{
	iterator += offset;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename I > void advance_v1(I & iterator, int offset)
{
    advance(iterator, offset, typename std::iterator_traits < I > ::iterator_category());
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template < std::forward_iterator I > void advance_v2(I & iterator, int offset)
{
	if (offset > 0) 
	{ 
		while (--offset >= 0)
		{
			++iterator;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template < std::bidirectional_iterator I > void advance_v2(I & iterator, int offset)
{
	if (offset > 0)
	{
		while (--offset >= 0)
		{
			++iterator;
		}
	}
	else
	{
		while (++offset <= 0)
		{
			--iterator;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template < std::random_access_iterator I > void advance_v2(I & iterator, int offset)
{
	iterator += offset;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		using category_1_t = std::forward_list < int > ::iterator::iterator_category;

		using category_2_t = std::        list < int > ::iterator::iterator_category;

		using category_3_t = std::      vector < int > ::iterator::iterator_category;

		static_assert(std::is_same_v < category_1_t, std::      forward_iterator_tag > );

		static_assert(std::is_same_v < category_2_t, std::bidirectional_iterator_tag > );

		static_assert(std::is_same_v < category_3_t, std::random_access_iterator_tag > );
	}

//  -------------------------------------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		assert(std::distance(vector.begin(), vector.end()) == 5);

		auto iterator = vector.begin();

			 advance_v1(iterator, 1); assert(*iterator == 2);

			 advance_v2(iterator, 1); assert(*iterator == 3);

		std::advance   (iterator, 1); assert(*iterator == 4);

		assert(*std::next(iterator, 1) == 5);

		assert(*std::prev(iterator, 1) == 3);
	}

//  -------------------------------------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		for (auto iterator = std::  begin(vector); iterator != std::  end(vector); ++iterator);

		for (auto iterator = std:: cbegin(vector); iterator != std:: cend(vector); ++iterator);

		for (auto iterator = std:: rbegin(vector); iterator != std:: rend(vector); ++iterator);

		for (auto iterator = std::crbegin(vector); iterator != std::crend(vector); ++iterator);
	}

//  -------------------------------------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		auto iterator = std::begin(vector);

		vector.resize(1'000);

		std::ignore = *iterator; // support: -D_GLIBCXX_DEBUG
	}
}