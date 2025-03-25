#include <cassert>
#include <memory>

///////////////////////////////////////////////////

int main()
{
	std::shared_ptr < int > x1;

	std::shared_ptr < int > x2(new auto(2));

	std::shared_ptr < int > x3(x2);

//  -----------------------------------------------

	assert(x2.use_count() == 2 && *x2 == 2);

	assert(x3.use_count() == 2 && *x3 == 2);

//  -----------------------------------------------

	x3.reset(new auto(3));

//  -----------------------------------------------

	assert(x2.use_count() == 1 && *x2 == 2);

	assert(x3.use_count() == 1 && *x3 == 3);

//  -----------------------------------------------

	auto x4 = new auto(1);

//	std::shared_ptr < int > x5(x4); // bad

//  -----------------------------------------------

//	assert(x5.use_count() == 1 && *x5 == 1); // bad

//  -----------------------------------------------

	delete x4;
}