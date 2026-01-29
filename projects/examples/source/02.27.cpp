////////////////////////////////////////////////////////

// chapter : Basics of Programming

////////////////////////////////////////////////////////

// section : Memory Management

////////////////////////////////////////////////////////

// content : Constant Pointers
//
// content : Pointers to Constant Objects

////////////////////////////////////////////////////////

int main()
{
    auto       x = 1;
		  
	auto const y = 2;

//  ----------------------------------------------------

	[[maybe_unused]] int       * const z1 = &x;

//	[[maybe_unused]] int       * const z2 = &y; // error

//	[[maybe_unused]] int       * const z3 = &3; // error

//  ----------------------------------------------------

	[[maybe_unused]] int const *       z4 = &x;

	[[maybe_unused]] int const *       z5 = &y;

//	[[maybe_unused]] int const *       z6 = &3; // error

//  ----------------------------------------------------

	[[maybe_unused]] int const * const z7 = &x;

	[[maybe_unused]] int const * const z8 = &y;

//	[[maybe_unused]] int const * const z9 = &3; // error
}

////////////////////////////////////////////////////////