///////////////////////////////////////////////////////////////////////

#include <boost/multi_array.hpp>

///////////////////////////////////////////////////////////////////////

int main()
{
	auto size = 5uz;

//  -------------------------------------------------------------------

	boost::multi_array < int, 2 > array(boost::extents[size][size]);

//  -------------------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			array[i][j] = j + 1;
		}
	}

//  -------------------------------------------------------------------

	using range_t = boost::multi_array_types::index_range;

//  -------------------------------------------------------------------

	auto view = array[boost::indices[range_t(0, 2)][range_t(0, 5, 2)]];

//  -------------------------------------------------------------------

	assert(view[0][0] == 1 && view[0][1] == 3 && view[0][2] == 5);

	assert(view[1][0] == 1 && view[1][1] == 3 && view[1][2] == 5);
}

///////////////////////////////////////////////////////////////////////