#include <cassert>
#include <memory>
#include <string>

/////////////////////////////////////////////////////////

int main()
{
	std::allocator < std::string > allocator;

//  -----------------------------------------------------

	std::allocator_traits < decltype(allocator) > traits;

//  -----------------------------------------------------

	auto ptr = traits.allocate(allocator, 1);

//  -----------------------------------------------------

	traits.construct (allocator, ptr, "aaaaa");

	traits.destroy   (allocator, ptr);

//  -----------------------------------------------------

	traits.deallocate(allocator, ptr, 1);
}