///////////////////////////////////////////

// chapter : Projects and Libraries

///////////////////////////////////////////

// section : Project Structure

///////////////////////////////////////////

// content : Pattern Pimpl
//
// content : Interfaces and Implementations
//
// content : Compile-Time Dependencies

///////////////////////////////////////////

#pragma once

///////////////////////////////////////////

#include <boost/noncopyable.hpp>

///////////////////////////////////////////

class Entity : private boost::noncopyable
{
public :

    Entity();

//  -------------------------------------

    Entity(Entity && other);

//  -------------------------------------

   ~Entity();

//  -------------------------------------

    auto & operator=(Entity && other);

//  -------------------------------------

    void test() const;

private :

	class Implementation;

//  -------------------------------------

    Implementation * m_pimpl = nullptr;
};

///////////////////////////////////////////