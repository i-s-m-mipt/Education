#include "06.02.project.header.hpp"

#include <iostream>

//  ================================================================================================

void test_v1()
{
	std::clog << "test_v1\n";
}

//  ================================================================================================

void Entity::test_v2()
{
	std::clog << "Entity::test_v2\n";
}

//  ================================================================================================

int global_x1 = 1;

namespace 
{ 
	[[maybe_unused]] int global_x2 = 2; 
}

       const int global_x3 = 3;
	   
extern const int global_x4 = 4;

//  ================================================================================================

namespace education::examples
{
	void test(Entity)
	{
		std::clog << "education::examples::test\n";
	}
}