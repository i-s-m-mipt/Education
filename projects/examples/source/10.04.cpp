//////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector;

//  ----------------------------------------------------------------------------------
		
	vector.reserve      (5); assert(std::size(vector) == 0 && vector.capacity() == 5);

	vector.resize       (5); assert(std::size(vector) == 5 && vector.capacity() == 5);

//  ----------------------------------------------------------------------------------

	vector.clear        ( ); assert(std::size(vector) == 0 && vector.capacity() == 5);

	vector.shrink_to_fit( ); assert(std::size(vector) == 0 && vector.capacity() == 0);

//  ----------------------------------------------------------------------------------

	vector.push_back    (1); assert(std::size(vector) == 1 && vector.capacity() >= 1);

	vector.shrink_to_fit( ); assert(std::size(vector) == 1 && vector.capacity() == 1);

//  ----------------------------------------------------------------------------------

	vector.pop_back     ( ); assert(std::size(vector) == 0 && vector.capacity() == 1);

	vector.shrink_to_fit( ); assert(std::size(vector) == 0 && vector.capacity() == 0);
}

//////////////////////////////////////////////////////////////////////////////////////