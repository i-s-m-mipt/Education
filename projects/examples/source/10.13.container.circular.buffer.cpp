#include <cassert>
#include <iostream>
#include <iterator>

#include <boost/circular_buffer.hpp>

//  ================================================================================================

template < typename I > inline void print(I first, I last)
{
	for (auto iterator = first; iterator != last; ++iterator)
	{
		std::cout << *iterator << ' ';
	}

	std::cout << std::endl;
}

//  ================================================================================================

int main()
{
	constexpr std::size_t capacity = 3;

	boost::circular_buffer < int > buffer(capacity);

	assert(std::size(buffer) == 0 && buffer.capacity() == capacity);

//  ================================================================================================

	buffer.push_back(0); print(std::begin(buffer), std::end(buffer));
	buffer.push_back(1); print(std::begin(buffer), std::end(buffer));
	buffer.push_back(2); print(std::begin(buffer), std::end(buffer));
	buffer.push_back(3); print(std::begin(buffer), std::end(buffer)); // note: overwrites 0
	buffer.push_back(4); print(std::begin(buffer), std::end(buffer)); // note: overwrites 1

	assert(buffer[0] == 2);
	assert(buffer[1] == 3);
	assert(buffer[2] == 4);

//  ================================================================================================

	assert(!buffer.is_linearized());

	boost::circular_buffer < int > ::array_range array_1, array_2;

	array_1 = buffer.array_one(); assert(array_1.second == 1);
	array_2 = buffer.array_two(); assert(array_2.second == 2);

	buffer.linearize();

	assert(buffer.is_linearized());

	array_1 = buffer.array_one(); assert(array_1.second == 3);
	array_2 = buffer.array_two(); assert(array_2.second == 0);

	return 0;
}