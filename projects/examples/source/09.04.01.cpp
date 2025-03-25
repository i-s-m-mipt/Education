#include <memory>

/////////////////////////////////////

int main()
{
	std::allocator < int > allocator;

//  ---------------------------------

	auto x = allocator.allocate(1);

	*x = 1;

	allocator.deallocate(x, 1);
}