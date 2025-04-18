///////////////////////////////////////////

#include <cassert>
#include <memory>

///////////////////////////////////////////

int main()
{
	std::shared_ptr < int > x(new auto(2));

	std::shared_ptr < int > y = x;

//  ---------------------------------------

	assert(x.use_count() == 2 && *x == 2);

	assert(y.use_count() == 2 && *y == 2);

//  ---------------------------------------

	y.reset(new auto(3));

//  ---------------------------------------

	assert(x.use_count() == 1 && *x == 2);

	assert(y.use_count() == 1 && *y == 3);

//  ---------------------------------------

	auto z = new auto(1);

//  ---------------------------------------

	y.reset(z);

//  ---------------------------------------

	assert(y.use_count() == 1 && *y == 1);

//  ---------------------------------------

//	delete z; // error
}

///////////////////////////////////////////