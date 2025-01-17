#include <cassert>
#include <concepts>
#include <forward_list>
#include <iterator>
#include <list>
#include <type_traits>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename I > void advance(I & iterator, int distance, std::forward_iterator_tag)
{
	if (distance > 0) 
	{
		while (--distance >= 0)
		{
			++iterator;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename I > void advance(I & iterator, int distance, std::bidirectional_iterator_tag)
{
	if (distance > 0)
	{
		while (--distance >= 0)
		{
			++iterator;
		} 
	}
	else
	{
		while (++distance <= 0)
		{
			--iterator;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename I > void advance(I & iterator, int distance, std::random_access_iterator_tag)
{
	iterator += distance;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename I > void advance_v1(I & iterator, int distance)
{
    advance(iterator, distance, typename std::iterator_traits < I > ::iterator_category());
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template < std::forward_iterator I > void advance_v2(I & iterator, int distance)
{
	if (distance > 0) 
	{ 
		while (--distance >= 0)
		{
			++iterator;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template < std::bidirectional_iterator I > void advance_v2(I & iterator, int distance)
{
	if (distance > 0)
	{
		while (--distance >= 0)
		{
			++iterator;
		}
	}
	else
	{
		while (++distance <= 0)
		{
			--iterator;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template < std::random_access_iterator I > void advance_v2(I & iterator, int distance)
{
	iterator += distance;
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

		auto begin = vector.begin();

			 advance_v1(begin, 1); assert(*begin == 2);

			 advance_v2(begin, 1); assert(*begin == 3);

		std::advance   (begin, 1); assert(*begin == 4);

		assert(*std::next(begin, 1) == 5);

		assert(*std::prev(begin, 1) == 3);
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

		auto begin = std::begin(vector);

		vector.resize(1'000);

		[[maybe_unused]] auto x = *begin; // support: -D_GLIBCXX_DEBUG
	}
}