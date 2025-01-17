#include <cassert>
#include <iterator>

#include <boost/circular_buffer.hpp>

//////////////////////////////////////////////////////////////////

int main()
{
	auto capacity = 3uz;

	boost::circular_buffer < int > buffer(capacity);

	assert(buffer.size() == 0 && buffer.capacity() == capacity);

	for (auto i = 0; i < 5; ++i)
	{
		buffer.push_back(i + 1);
	}

	assert(buffer[0] == 3 && buffer[1] == 4 && buffer[2] == 5);

	assert(!buffer.is_linearized());

	boost::circular_buffer < int > ::array_range array_1, array_2;

	array_1 = buffer.array_one(); assert(array_1.second == 1);

	array_2 = buffer.array_two(); assert(array_2.second == 2);

	buffer.linearize();

	assert(buffer.is_linearized());

	array_1 = buffer.array_one(); assert(array_1.second == 3);

	array_2 = buffer.array_two(); assert(array_2.second == 0);
}