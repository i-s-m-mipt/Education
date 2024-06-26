#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main()
{
	std::allocator < int > allocator_int;

	const auto ptr_int = allocator_int.allocate(1);

	*ptr_int = 42;

	allocator_int.deallocate(ptr_int, 1);

//  ================================================================================================

	std::vector < int, std::allocator < int > > vector;

	std::allocator < std::string > allocator_string;

	std::allocator_traits < decltype(allocator_string) > allocator_traits;

	const auto ptr_string = allocator_traits.allocate(allocator_string, 1);

//	std::cout << *ptr_string << std::endl; // bad

	allocator_traits.construct(allocator_string, ptr_string, "Hello, world!");

	std::cout << *ptr_string << std::endl;

	allocator_traits.destroy(allocator_string, ptr_string);

	allocator_traits.deallocate(allocator_string, ptr_string, 1);

	return 0;
}