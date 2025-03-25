#include <cassert>
#include <utility>

#include <boost/noncopyable.hpp>

/////////////////////////////////////////////////////////////////

template < typename T > class Unique : private boost::noncopyable
{
public :

    Unique(T * x = nullptr) : m_x(x) {}
        
    Unique(Unique && other) : Unique() 
    { 
        swap(other);
    }

    auto & operator=(Unique && other)
    { 
        reset(other.release());
        
        return *this;
    }

   ~Unique() 
    { 
        reset();
    }

//  ------------------------------------------

    void swap(Unique & other)
    { 
        std::swap(m_x, other.m_x);
    }

//  ------------------------------------------

    auto release()
    {
        return std::exchange(m_x, nullptr);
    }

    void reset(T * x = nullptr) 
    {
        if (m_x)
        {
            delete m_x;
        }

        m_x = x;
    }
     
private :

    T * m_x = nullptr;
};

/////////////////////////////////////////////////////////////////

int main()
{
    Unique < int > unique_1;

    Unique < int > unique_2(new auto(2));

    Unique < int > unique_3(new auto(3));

//  ----------------------------------------------

//  Unique < int > unique_3 = unique_2; // error

//                 unique_3 = unique_2; // error

//  ----------------------------------------------

    Unique < int > unique_4 = std::move(unique_3);

                   unique_4 = std::move(unique_3);
}