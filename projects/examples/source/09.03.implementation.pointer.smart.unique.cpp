#include <cassert>
#include <utility>

#include <boost/noncopyable.hpp>

/////////////////////////////////////////////////////////////////////////

template < typename T > class Unique : private boost::noncopyable
{
public:

    Unique(T * data = nullptr) : m_data(data) {}
        
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

//  -------------------------------------------------------------

    void swap(Unique & other)
    { 
        std::swap(m_data, other.m_data); 
    }

//  -------------------------------------------------------------

    auto release()
    {
        return std::exchange(m_data, nullptr);
    }

    void reset(T * data = nullptr) 
    {
        if (m_data)
        {
            delete m_data;
        }

        std::exchange(m_data, data);
    }

//  -------------------------------------------------------------

    auto & operator*() const
    { 
        return *m_data; 
    }
     
private:

    T * m_data = nullptr;
};

/////////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > auto make_unique(Ts && ... args)
{
    return Unique < T > (new T(std::forward < Ts > (args)...)); 
}

/////////////////////////////////////////////////////////////////////////

int main()
{
    Unique < int > unique_1;

    Unique < int > unique_2(new auto(2));

//  ---------------------------------------------

//  Unique < int > unique_3(unique_2); // error

    Unique < int > unique_4(std::move(unique_2));

//  unique_3 = unique_2; // error
    
    unique_4 = std::move(unique_2);

//  ---------------------------------------------

    assert(*unique_4 == 2);

//  ---------------------------------------------

    auto unique_5 = make_unique < int > (5);
}