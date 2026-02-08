///////////////////////////////////////////

// chapter : Memory Management

///////////////////////////////////////////

// section : Resource Handlers

///////////////////////////////////////////

// content : Garbage Collectors
//
// content : Smart Pointers
//
// content : Pointer std::shared_ptr
//
// content : Reference Counting
//
// content : Plain and Smart Pointers

///////////////////////////////////////////

#include <cassert>
#include <memory>

///////////////////////////////////////////

int main()
{
	std::shared_ptr < int > x(new auto(1));

	std::shared_ptr < int > y = x;

//  ---------------------------------------

	assert(x.use_count() == 2 && *x == 1);

	assert(y.use_count() == 2 && *y == 1);

//  ---------------------------------------

	y.reset(new auto(2));

//  ---------------------------------------

	assert(x.use_count() == 1 && *x == 1);

	assert(y.use_count() == 1 && *y == 2);

//  ---------------------------------------

	auto z = new auto(3);

//  ---------------------------------------

	y.reset(z);

//  ---------------------------------------

	assert(y.use_count() == 1 && *y == 3);

//  ---------------------------------------

//	delete z; // error
}

///////////////////////////////////////////