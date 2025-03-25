#include <iostream>

#include "06.01.09.hpp"

//////////////////////////////////////////////////////

class Entity::Implementation
{
public :

    void test() const
    { 
        std::cout << "Entity::Implementation::test\n";
    }
};

//////////////////////////////////////////////////////

Entity:: Entity() : m_pimpl(new Implementation) {}

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