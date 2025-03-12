#include <cassert>
#include <memory>

/////////////////////////////////////////////////////////

int main()
{
	std::shared_ptr < int > ptr_1;

	std::shared_ptr < int > ptr_2(new auto(2));

	std::shared_ptr < int > ptr_3(ptr_2);

//  -----------------------------------------------------

	assert(ptr_2.use_count() == 2 && *ptr_2 == 2);

	assert(ptr_3.use_count() == 2 && *ptr_3 == 2);

//  -----------------------------------------------------

	ptr_3.reset(new auto(3));

//  -----------------------------------------------------

	assert(ptr_2.use_count() == 1 && *ptr_2 == 2);

	assert(ptr_3.use_count() == 1 && *ptr_3 == 3);

//  -----------------------------------------------------

	auto ptr = new auto(1);

//	std::shared_ptr < int > ptr_4(ptr); // bad

//  -----------------------------------------------------

//	assert(ptr_4.use_count() == 1 && *ptr_4 == 1); // bad

//  -----------------------------------------------------

	delete ptr;
}