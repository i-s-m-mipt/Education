//////////////////////////////////////////////////////////////////

// chapter : Basics of Programming

//////////////////////////////////////////////////////////////////

// section : Types and Variables

//////////////////////////////////////////////////////////////////

// content : Variable Type Inference
//
// content : Type Placeholder auto
//
// content : Container std::initializer_list
//
// content : Type Specifier decltype

//////////////////////////////////////////////////////////////////

#include <initializer_list>
#include <type_traits>

//////////////////////////////////////////////////////////////////

int main()
{
//	[[maybe_unused]] auto x1; // error

//	[[maybe_unused]] auto x2{}; // error

    [[maybe_unused]] auto x3(3);

	[[maybe_unused]] auto x4 = 4;

    [[maybe_unused]] auto x5 { 5 };

//	[[maybe_unused]] auto x6 = { 6 }; // bad

//  --------------------------------------------------------------

    static_assert(std::is_same_v < decltype(x3), int > );

    static_assert(std::is_same_v < decltype(x4), int > );

    static_assert(std::is_same_v < decltype(x5), int > );

//  --------------------------------------------------------------

    [[maybe_unused]] auto y1 = 1u;

//	[[maybe_unused]] auto y2 = 2, y3 = 3.0; // error

//  --------------------------------------------------------------

    static_assert(std::is_same_v < decltype(y1), unsigned int > );
}

//////////////////////////////////////////////////////////////////