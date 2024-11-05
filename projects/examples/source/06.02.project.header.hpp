#ifndef PROJECT_HEADER_HPP
#define PROJECT_HEADER_HPP

#pragma once

#include <iostream>

//  ================================================================================================

void test_v1();
void test_v2();

//  ================================================================================================

//  void test_v3() // error
//  { 
//	    std::clog << "test_v3\n"; 
//  } 

//  ================================================================================================

inline void test_v4()
{ 
    std::clog << "test_v4\n"; 
}

//  ================================================================================================

template < typename T > void test_v5()
{
	std::clog << "test_v5\n";
}

//  ================================================================================================

struct Entity_v1 
{ 
	static void test_v1()
	{ 
		std::clog << "Entity_v1::test_v1\n"; 
	} 

	static void test_v2();
};

//  ================================================================================================

extern       int global_x1;
extern       int global_x2;
extern const int global_x3;
extern const int global_x4;

//  ================================================================================================

namespace education
{
	namespace examples
	{
		struct Entity_v2 {};
	}
}

namespace education
{
	namespace examples
	{
		void test(Entity_v2);
	}
}

//  ================================================================================================

namespace constants
{
//					 auto x1 = 1; // error

//		   const     auto x2 = 2; // bad

	inline const     auto x3 = 3;
	
		   constexpr auto x4 = 4;
}

#endif