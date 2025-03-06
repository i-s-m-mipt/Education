#pragma once

////////////////////////////////////////////////////////

#include <utility>

#include <boost/noncopyable.hpp>

////////////////////////////////////////////////////////

class Entity : private boost::noncopyable
{
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

//  ----------------------------------------------------

    void test() const;

private:

	class Implementation;

//  ----------------------------------------------------

    Implementation * m_pimpl = nullptr;
};