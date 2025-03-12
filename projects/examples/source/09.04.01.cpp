#include <memory>

/////////////////////////////////////

int main()
{
	std::allocator < int > allocator;

//  ---------------------------------

	auto ptr = allocator.allocate(1);

	*ptr = 1;

	allocator.deallocate(ptr, 1);
}