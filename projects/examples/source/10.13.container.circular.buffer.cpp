#include <cassert>
#include <iterator>

#include <boost/circular_buffer.hpp>

////////////////////////////////////////////////////////////////////

int main()
{
	auto capacity = 3uz;

	boost::circular_buffer < int > buffer(capacity);

	assert(std::size(buffer) == 0 && buffer.capacity() == capacity);

//  ----------------------------------------------------------------

	buffer.push_back(1);
	buffer.push_back(2);
	buffer.push_back(3);
	buffer.push_back(4); 
	buffer.push_back(5);

	assert(buffer[0] == 3 && buffer[1] == 4 && buffer[2] == 5);

//  ----------------------------------------------------------------

	assert(!buffer.is_linearized());

	boost::circular_buffer < int > ::array_range array_1, array_2;

	array_1 = buffer.array_one(); assert(array_1.second == 1);
	array_2 = buffer.array_two(); assert(array_2.second == 2);

	buffer.linearize();

	assert(buffer.is_linearized());

	array_1 = buffer.array_one(); assert(array_1.second == 3);
	array_2 = buffer.array_two(); assert(array_2.second == 0);
}