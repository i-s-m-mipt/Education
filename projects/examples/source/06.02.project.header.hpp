#ifndef PROJECT_HEADER_HPP
#define PROJECT_HEADER_HPP

#pragma once

#include <iostream>
#include <utility>

#include <boost/noncopyable.hpp>

////////////////////////////////////////////////////////

void test_v2();

void test_v3();

////////////////////////////////////////////////////////

//  void test_v4() // error
//  { 
//	    std::cout << "test_v4\n"; 
//  } 

////////////////////////////////////////////////////////

inline void test_v5()
{ 
    std::cout << "test_v5\n"; 
}

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

////////////////////////////////////////////////////////

template < typename T > void test_v6()
{
	std::cout << "test_v6\n";
}

////////////////////////////////////////////////////////

extern       int global_x1;

extern       int global_x2;

extern const int global_x3;

extern const int global_x4;

       const int global_x5 = 5;

inline const int global_x6 = 6;

////////////////////////////////////////////////////////

#endif