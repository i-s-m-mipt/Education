#include <cassert>
#include <new>
#include <utility>

/////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Optional 
{
public:

    Optional() = default;

    Optional(T x) 
    { 
        initialize(x); 
    }

    Optional(const Optional & other) 
    {
        if (!other.empty()) 
        {
            initialize(*other.m_data);
        }
    }

    Optional(Optional && other) : m_data(other.m_data)
    {
        other.m_data = nullptr;
    }

    auto & operator=(const Optional & other) 
    {
        if (this != &other)
        {
            destroy();
            
            if (!other.empty()) 
            {
                construct(*other.m_data); 
            }
            else 
            {
                deallocate();
            }
        }

        return *this;
    }

    auto & operator=(Optional && other)
    {
        if (this != &other)
		{
            uninitialize(); m_data = other.m_data; other.m_data = nullptr;
		}

		return *this;
    } 

    auto & operator=(T x) 
    {
        destroy(); construct(x); 
        
        return *this;
    }

   ~Optional() 
    { 
        uninitialize(); 
    }

//  -----------------------------------------------------------------------------------------

    auto empty() const 
    { 
        return !m_data;
    }

    auto data   (   ) const { return *m_data; }

    auto data_or(T x) const
    { 
        return m_data ? *m_data : x; 
    }

private:

    void initialize(T x) 
    { 
        allocate(); 
        
        construct(x); 
    }

    void allocate() 
    { 
        m_data = static_cast < T * > (operator new(sizeof(T), std::align_val_t(alignof(T))));
    }

    void construct(T x) 
    {
        if (!m_data) 
        {
            allocate(); 
        }
        
        new(m_data) T(x); 
    }

    void uninitialize() 
    { 
        destroy(); 
        
        deallocate(); 
    }

    void destroy() 
    { 
        if (m_data) 
        {
            m_data->~T();
        } 
    }

    void deallocate()
    { 
        if (m_data)
        {
            operator delete(m_data, sizeof(T), std::align_val_t(alignof(T))); 
            
            m_data = nullptr;
        }
    }

//  -----------------------------------------------------------------------------------------

    T * m_data = nullptr;
}; 

/////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > auto make_optional(T && x)
{ 
    return Optional < T > (std::forward < T > (x)); 
}

/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        Optional < int > optional_1;
    
        Optional < int > optional_2 = 2;

        Optional < int > optional_3(optional_2);

        Optional < int > optional_4(std::move(optional_3));

        optional_3 = optional_2; 
    
        optional_4 = std::move(optional_3);

        optional_4 = 4;
    }

//  -------------------------------------------------------

    {
        assert(make_optional(1).data_or(2) == 1);
    }    
}