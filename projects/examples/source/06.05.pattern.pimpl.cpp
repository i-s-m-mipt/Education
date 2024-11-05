#include <iostream>
#include <utility>

#include <boost/noncopyable.hpp>

//  ================================================================================================

class Entity : private boost::noncopyable // detail: header.hpp
{
private:

    struct Implementation;

public:

    Entity();

    Entity(Entity && other) : m_pimpl(other.m_pimpl)
    {
        other.m_pimpl = nullptr;
    }

    auto & operator=(Entity && other)
    {
        m_pimpl = std::exchange(other.m_pimpl, nullptr); 
        
        return *this;
    }

   ~Entity();

//  ------------------------------------------------------------------------------------------------

    void test() const;

private:

    Implementation * m_pimpl = nullptr;
};

//  ================================================================================================

struct Entity::Implementation // detail: source.cpp
{
    void test() const
    { 
        std::clog << "Entity::Implementation::test\n"; 
    }
};

//  ================================================================================================

Entity:: Entity() : m_pimpl(new Implementation()) {}

Entity::~Entity() 
{ 
    if (m_pimpl)
    {
        delete m_pimpl;
    }
}

//  ================================================================================================

void Entity::test() const
{ 
    m_pimpl->test(); 
}

//  ================================================================================================

int main()
{
    Entity().test();
}