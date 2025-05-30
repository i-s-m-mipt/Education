//////////////////////////////////////

#ifndef PROJECT_HEADER_HPP

#define PROJECT_HEADER_HPP

//////////////////////////////////////

#pragma once

//////////////////////////////////////

#include <iostream>

//////////////////////////////////////

void test_v1();

void test_v2();

//////////////////////////////////////

// void test_v3() // error
// { 
//     std::cout << "test_v3\n";
// } 

//////////////////////////////////////

inline void test_v4()
{ 
    std::cout << "test_v4\n";
}

//////////////////////////////////////

template < typename T > void test_v5()
{
	std::cout << "test_v5\n";
}

//////////////////////////////////////

extern int       g_x1;

extern int       g_x2;

extern int const g_x3;

extern int const g_x4;

//////////////////////////////////////

       int const g_x5 = 5;

inline int const g_x6 = 6;

//////////////////////////////////////

#endif

//////////////////////////////////////