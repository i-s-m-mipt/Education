#include <iostream>
#include <vector>

//  ================================================================================================

struct Structure { int x{}, y{}, z = 4; };

//  ================================================================================================

struct Point { double x = 0.0; double y = 0.0; };

//  ================================================================================================

[[nodiscard]] inline Point make_point(double x, double y)
{
	return (x * y > 0.0 ? Point { x, y } : Point{});
}

//  ================================================================================================

int main()
{
	[[maybe_unused]] Structure s1            ; // elements: { 0, 0, 4 }
	[[maybe_unused]] Structure s2 {         }; // elements: { 0, 0, 4 }
	[[maybe_unused]] Structure s3 { 1       }; // elements: { 1, 0, 4 }
	[[maybe_unused]] Structure s4 { 1, 2    }; // elements: { 1, 2, 4 }
	[[maybe_unused]] Structure s5 { 1, 2, 3 }; // elements: { 1, 2, 3 }

	[[maybe_unused]] Structure s6 { .x = 1, .z = 3 }; // elements: { 1, 0, 3 }
	
//	[[maybe_unused]] Structure s7 { .y = 2, .x = 1 }; // error

//  ================================================================================================

	s1.x = 42;

	const auto ptr = &s1; // detail: Structure * const

//	(*ptr).y = 42; // bad

	ptr->y = 42;

	auto & ref = s1.z; // detail: int &

	ref = 42;

//  ================================================================================================

	std::cout <<  s1.x << std::endl; // output: 42
	std::cout <<  s1.y << std::endl; // output: 42
	std::cout <<  s1.z << std::endl; // output: 42

	std::cout << &s1   << std::endl; // output: 0x...
	std::cout << &s1.x << std::endl; // output: 0x...

//  ================================================================================================

	s1 = { 1, 2, 3 };

	s1 = { .x = 1, .z = 3 };

//  ================================================================================================

	[[maybe_unused]] const Structure s8 { 1, 2, 3 };

//	s8.x = 42; // error

//  ================================================================================================

	std::vector < Point > points { make_point(0.0, 0.0), { 1.0, 1.0 } };

	return 0;
}