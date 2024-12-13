#include "06.02.project.header.hpp"

#include <iostream>

import demo.submodule;

//////////////////////////////////////////////////////

void test_v2()
{
	std::clog << "test_v2\n";
}

//////////////////////////////////////////////////////

class Entity::Implementation
{
public:

    void test() const
    { 
        std::clog << "Entity::Implementation::test\n"; 
    }
};

//////////////////////////////////////////////////////

Entity:: Entity() : m_pimpl(new Implementation()) {}

Entity::~Entity() 
{ 
    if (m_pimpl)
    {
        delete m_pimpl;
    }
}

//////////////////////////////////////////////////////

void Entity::test() const
{ 
    m_pimpl->test(); 
}

//////////////////////////////////////////////////////

int global_x1 = 1;

namespace 
{ 
	[[maybe_unused]] int global_x2 = 2; 
}

       const int global_x3 = 3;
	   
extern const int global_x4 = 4;