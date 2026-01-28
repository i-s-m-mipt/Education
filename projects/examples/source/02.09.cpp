////////////////////////////////////////////////////

// chapter : Basics of Programming

////////////////////////////////////////////////////

// section : Objects and Variables

////////////////////////////////////////////////////

// content : Type Inference
//
// content : Type Placeholder auto
//
// content : Container std::initializer_list
//
// content : Separator ,

////////////////////////////////////////////////////

#include <initializer_list>

////////////////////////////////////////////////////

int main()
{
//	[[maybe_unused]] auto x1; // error

//	[[maybe_unused]] auto x2{}; // error

    [[maybe_unused]] auto x3(3);

	[[maybe_unused]] auto x4 = 4;

    [[maybe_unused]] auto x5 { 5 };

//	[[maybe_unused]] auto x6 = { 6 }; // bad

//  ------------------------------------------------

    [[maybe_unused]] auto y1 = 1u;

//	[[maybe_unused]] auto y2 = 2, y3 = 3.0; // error
}

////////////////////////////////////////////////////