#include <iostream>

#include "06.01.05.hpp"

//////////////////////////////////

void test_v2()
{
	std::cout << "test_v2\n";
}

//////////////////////////////////

int g_x1 = 1;

namespace 
{ 
	[[maybe_unused]] int g_x2 = 2;
}

       const int g_x3 = 3;
	   
extern const int g_x4 = 4;