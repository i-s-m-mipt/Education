///////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <concepts>
#include <iterator>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename I > void advance(I & iterator, int offset, std::random_access_iterator_tag)
{
	iterator += offset;
}

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename I > void advance_v1(I & iterator, int offset)
{
    advance(iterator, offset, typename std::iterator_traits < I > ::iterator_category());
}

///////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////

template < std::random_access_iterator I > void advance_v2(I & iterator, int offset)
{
	iterator += offset;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  ------------------------------------------------

	auto iterator = std::begin(vector);

//  ------------------------------------------------

	advance_v1(iterator, 1); assert(*iterator == 2);

	advance_v2(iterator, 1); assert(*iterator == 3);
}

///////////////////////////////////////////////////////////////////////////////////////////////