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

	auto string = traits.allocate(allocator, 1);

//  -----------------------------------------------------

	traits.construct (allocator, string, "aaaaa");

	traits.destroy   (allocator, string);

//  -----------------------------------------------------

	traits.deallocate(allocator, string, 1);
}