#include <cassert>
#include <memory>
#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		std::allocator < int > allocator;

		auto ptr = allocator.allocate(1);

		*ptr = 1;

		allocator.deallocate(ptr, 1);
	}

//  --------------------------------------------------------------------------

	{
		std::allocator < std::string > allocator;

		std::allocator_traits < decltype(allocator) > traits;

		auto ptr = traits.allocate(allocator, 1);

//		assert(std::empty(*ptr)); // bad

		traits.construct (allocator, ptr, "aaaaa");

		traits.destroy   (allocator, ptr);

		traits.deallocate(allocator, ptr, 1);
	}

//  --------------------------------------------------------------------------

	{
		std::vector < int, std::allocator < int > > vector = { 1, 2, 3, 4, 5};
	}
}