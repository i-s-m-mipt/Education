#include <cassert>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto size = 5uz;

	std::vector < int > vector;

//  ------------------------------------------------------------------------------------------------
		
	vector.resize(2 * size); assert(std::size(vector) == size * 2 && vector.capacity() == size * 2);

	vector.resize    (size); assert(std::size(vector) == size     && vector.capacity() == size * 2);

//  ------------------------------------------------------------------------------------------------

	vector.shrink_to_fit (); assert(std::size(vector) == size     && vector.capacity() == size    );

	vector.clear         (); assert(std::size(vector) == 0        && vector.capacity() == size    );

	vector.shrink_to_fit (); assert(std::size(vector) == 0        && vector.capacity() == 0       );

//  ------------------------------------------------------------------------------------------------

	vector.reserve   (size); assert(std::size(vector) == 0        && vector.capacity() == size    );

	vector.resize    (size); assert(std::size(vector) == size     && vector.capacity() == size    );

//  ------------------------------------------------------------------------------------------------

	vector.push_back    (1); assert(std::size(vector) == size + 1 && vector.capacity() >= size + 1);

	vector.shrink_to_fit (); assert(std::size(vector) == size + 1 && vector.capacity() == size + 1);

	vector.pop_back      (); assert(std::size(vector) == size     && vector.capacity() == size + 1);

	vector.shrink_to_fit (); assert(std::size(vector) == size     && vector.capacity() == size    );
}