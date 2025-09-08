//////////////////////////////////////////////////////////////

#include <cassert>

//////////////////////////////////////////////////////////////

#include <boost/circular_buffer.hpp>

//////////////////////////////////////////////////////////////

int main()
{
	boost::circular_buffer < int > buffer(3);

//  ----------------------------------------------------------

	for (auto i = 0; i < 5; ++i)
	{
		buffer.push_back(i + 1);
	}

//  ----------------------------------------------------------

	assert(buffer.at(0) == 3);
	
	assert(buffer.at(1) == 4);
	
	assert(buffer.at(2) == 5);

//  ----------------------------------------------------------

	boost::circular_buffer < int > ::array_range array_1;
	
	boost::circular_buffer < int > ::array_range array_2;

//  ----------------------------------------------------------

	assert(buffer.is_linearized() == 0);

//  ----------------------------------------------------------

	array_1 = buffer.array_one(); assert(array_1.second == 1);

	array_2 = buffer.array_two(); assert(array_2.second == 2);

//  ----------------------------------------------------------

	buffer.linearize();

//  ----------------------------------------------------------

	assert(buffer.is_linearized() == 1);

//  ----------------------------------------------------------

	array_1 = buffer.array_one(); assert(array_1.second == 3);

	array_2 = buffer.array_two(); assert(array_2.second == 0);
}

//////////////////////////////////////////////////////////////