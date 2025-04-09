////////////////////////////////////////////////////////

int main()
{
    auto       x = 1;
		  
	auto const y = 2;

//  ----------------------------------------------------

	[[maybe_unused]] int       * const z1 = &x;

//	[[maybe_unused]] int       * const z2 = &y; // error

//  ----------------------------------------------------

	[[maybe_unused]] int const *       z3 = &x;

	[[maybe_unused]] int const *       z4 = &y;

//  ----------------------------------------------------

	[[maybe_unused]] int const * const z5 = &x;

	[[maybe_unused]] int const * const z6 = &y;
}

////////////////////////////////////////////////////////