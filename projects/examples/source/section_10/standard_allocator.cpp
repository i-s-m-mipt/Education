#include <iostream>
#include <memory>
#include <string>

int main()
{
	std::allocator < int > allocator_int;

	auto ptr_int = allocator_int.allocate(1);

	*ptr_int = 42; // note: acceptable for fundamental types, consider construct

	allocator_int.deallocate(ptr_int, 1);

	std::allocator < std::string > allocator_string;

	std::allocator_traits < decltype(allocator_string) > allocator_traits;

	auto ptr_string = allocator_traits.allocate(allocator_string, 1);

//	std::cout << *ptr_string << std::endl; // bad: object not constructed

	allocator_traits.construct(allocator_string, ptr_string, "Hello, allocator!");

	std::cout << *ptr_string << std::endl;

	allocator_traits.destroy(allocator_string, ptr_string);

	allocator_traits.deallocate(allocator_string, ptr_string, 1);

	return 0;
}