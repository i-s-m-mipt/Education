int main()
{
    	  auto x = 1;
	
	const auto y = 2;

//  ---------------------------------------------

	[[maybe_unused]]       int & z1 = x;

//	[[maybe_unused]]       int & z2 = y; // error

//  ---------------------------------------------

	[[maybe_unused]] const int & z3 = x;

	[[maybe_unused]] const int & z4 = y;

//  ---------------------------------------------

//	[[maybe_unused]]       int & z5 = 3; // error

    [[maybe_unused]] const int & z6 = 3;
}