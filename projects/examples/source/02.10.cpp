/////////////////////////////////////////////////////////////////////

// chapter : Language Core Basics

/////////////////////////////////////////////////////////////////////

// content : Implicit, Explicit, Narrow and Wide Type Conversions
//
// content : Temporary Objects
//
// content : C-Style and C++-Style Type Conversions
//
// content : Operator static_cast

/////////////////////////////////////////////////////////////////////

int main()
{
    double x = 1;

//  -----------------------------------------------------------------

//	[[maybe_unused]] int y1 = x; // bad

//	[[maybe_unused]] int y2 { x }; // error

//	[[maybe_unused]] int y3 { int(x) }; // bad

	[[maybe_unused]] int y4 { static_cast < int > (x) };

//  [[maybe_unused]] int y5 = static_cast < int > (-1); // bad

//  [[maybe_unused]] int y6 = static_cast < int > ("aaaaa"); // error
}

/////////////////////////////////////////////////////////////////////