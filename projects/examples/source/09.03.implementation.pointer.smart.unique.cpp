#include <cassert>
#include <cstddef>
#include <type_traits>
#include <utility>

#include <boost/noncopyable.hpp>

//  ================================================================================================

template < typename T > class Unique : private boost::noncopyable
{
public:

    explicit Unique(T * data = nullptr) : m_data(data) {}
        
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

//  ----------------------------------
        
    void swap(Unique & other)
    { 
        using std::swap; 

        swap(m_data, other.m_data); 
    }

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

//  --------------------------------------------

    auto & operator*() const
    { 
        return *m_data; 
    }
     
private:

    T * m_data = nullptr;
};

//  ================================================================================================

template < typename T, typename ... Ts > auto make_unique(Ts && ... args)
{
    return Unique < T > (new T(std::forward < Ts > (args)...)); 
}

//  ================================================================================================

int main()
{
    auto unique_1 = make_unique < int > (1);
    auto unique_2 = make_unique < int > (2);

    unique_2 = std::move(unique_1);

    assert(*unique_2 == 1);
}