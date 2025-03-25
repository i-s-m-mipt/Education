int main()
{
    	  auto x = 1;
		  
	const auto y = 2;

//  ----------------------------------------------------

	[[maybe_unused]]       int * const z1 = &x;

//	[[maybe_unused]]       int * const z2 = &y; // error

//  ----------------------------------------------------

	[[maybe_unused]] const int *       z3 = &x;

	[[maybe_unused]] const int *       z4 = &y;

//  ----------------------------------------------------

	[[maybe_unused]] const int * const z5 = &x;

	[[maybe_unused]] const int * const z6 = &y;
}