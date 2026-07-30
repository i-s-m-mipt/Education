////////////////////////////////////////////

// chapter : Projects and Libraries

////////////////////////////////////////////

// content : Header Files
//
// content : Declarations and Definitions
//
// content : One Definition Rule (ODR)
//
// content : Internal Linking
//
// content : Storage Class Specifier static
//
// content : Inline Functions
//
// content : Templates
//
// content : Explicit Template Instantiation
//
// content : Declaration extern
//
// content : Global Objects
//
// content : Variable Declarations
//
// content : Storage Class Specifier extern
//
// content : Inline Variables
//
// content : Variable Specifier inline
//
// content : Header Guards

////////////////////////////////////////////

#ifndef HEADER_06_05

#define HEADER_06_05

////////////////////////////////////////////

#pragma once

////////////////////////////////////////////

#include <print>

////////////////////////////////////////////

void test_v1();

void test_v2();

////////////////////////////////////////////

// void test_v3() // error
// {
//     std::print("test_v3\n");
// }

////////////////////////////////////////////

[[maybe_unused]] static void test_v4()
{
	std::print("test_v4\n");
}

////////////////////////////////////////////

inline void test_v5()
{
    std::print("test_v5\n");
}

////////////////////////////////////////////

template < typename T > void test_v6()
{
    std::print("test_v6\n");
}

////////////////////////////////////////////

extern template void test_v6 < int > ();

////////////////////////////////////////////

[[maybe_unused]] extern int g_x1;

[[maybe_unused]] static int g_x2 = 2;

[[maybe_unused]] inline int g_x3 = 3;

////////////////////////////////////////////

#endif

////////////////////////////////////////////