#include <cassert>
#include <memory>
#include <string>
#include <vector>

///////////////////////////////////////////////////////////////////////

int main()
{
	{
		std::allocator < int > allocator;

		auto object = allocator.allocate(1);

		*object = 1;

		assert(*object == 1);

		allocator.deallocate(object, 1);

		std::vector < int, std::allocator < int > > vector;
	}

//  -------------------------------------------------------------------

	{
		std::allocator < std::string > allocator;

		std::allocator_traits < decltype(allocator) > allocator_traits;

		auto object = allocator_traits.allocate(allocator, 1);

//		assert(std::empty(*object)); // bad

		allocator_traits.construct(allocator, object, "aaaaa");

		assert(*object == "aaaaa");

		allocator_traits.destroy(allocator, object);

		allocator_traits.deallocate(allocator, object, 1);
	}
}