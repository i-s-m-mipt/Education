/////////////////////////////////////////////////////////////////////////////////////////

// chapter : Memory Management

/////////////////////////////////////////////////////////////////////////////////////////

// section : Iterator Classification

/////////////////////////////////////////////////////////////////////////////////////////

// content : Iterator Classification
//
// content : Utility std::iterator_traits
//
// content : Forward Iterators
//
// content : Tag std::forward_iterator_tag
//
// content : Concept std::forward_iterator
//
// content : Bidirectional Iterators
//
// content : Tag std::bidirectional_iterator_tag
//
// content : Concept std::bidirectional_iterator
//
// content : Random Access Iterators
//
// content : Tag std::random_access_iterator_tag
//
// content : Concept std::random_access_iterator

/////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <concepts>
#include <iterator>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////

void advance(auto & iterator, int offset, std::forward_iterator_tag)
{
	if (offset > 0) 
	{
		while (--offset >= 0)
		{
			++iterator;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void advance(auto & iterator, int offset, std::bidirectional_iterator_tag)
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

/////////////////////////////////////////////////////////////////////////////////////////

void advance(auto & iterator, int offset, std::random_access_iterator_tag)
{
	iterator += offset;
}

/////////////////////////////////////////////////////////////////////////////////////////

template < typename I > void advance_v1(I & iterator, int offset)
{
    advance(iterator, offset, typename std::iterator_traits < I > ::iterator_category());
}

/////////////////////////////////////////////////////////////////////////////////////////

void advance_v2(std::forward_iterator auto & iterator, int offset)
{
	if (offset > 0) 
	{ 
		while (--offset >= 0)
		{
			++iterator;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void advance_v2(std::bidirectional_iterator auto & iterator, int offset)
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

/////////////////////////////////////////////////////////////////////////////////////////

void advance_v2(std::random_access_iterator auto & iterator, int offset)
{
	iterator += offset;
}

/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  ------------------------------------------------

	auto iterator = std::begin(vector);

//  ------------------------------------------------

	advance_v1(iterator, 1); assert(*iterator == 2);

	advance_v2(iterator, 1); assert(*iterator == 3);
}

/////////////////////////////////////////////////////////////////////////////////////////