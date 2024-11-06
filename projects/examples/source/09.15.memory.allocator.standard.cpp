#include <cassert>
#include <memory>
#include <string>
#include <vector>

int main()
{
	std::allocator < int > allocator_int;

	auto object_1 = allocator_int.allocate(1);

	*object_1 = 1;

	assert(*object_1 == 1);

	allocator_int.deallocate(object_1, 1);

	std::vector < int, std::allocator < int > > vector;

//  ================================================================================================

	std::allocator < std::string > allocator_string;

	std::allocator_traits < decltype(allocator_string) > allocator_traits;

	auto object_2 = allocator_traits.allocate(allocator_string, 1);

//	assert(std::empty(*object_2)); // bad

	allocator_traits.construct(allocator_string, object_2, "aaaaa");

	assert(*object_2 == "aaaaa");

	allocator_traits.destroy(allocator_string, object_2);

	allocator_traits.deallocate(allocator_string, object_2, 1);
}