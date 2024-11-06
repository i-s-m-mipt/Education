#include <cassert>
#include <new>
#include <utility>

//  ================================================================================================

template < typename T > class Optional 
{
public:

    Optional() = default;

    explicit Optional(T data) 
    { 
        initialize(data); 
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
            if (destroy(); !other.empty()) 
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

    auto & operator=(T data) 
    {
        destroy(); construct(data); 
        
        return *this;
    }

   ~Optional() 
    { 
        uninitialize(); 
    }

private:

    void initialize(T data) 
    { 
        allocate(); 
        
        construct(data); 
    }

    void allocate() 
    { 
        m_data = static_cast < T * > (::operator new(sizeof(T), std::align_val_t(alignof(T)))); 
    }

    void construct(T data) 
    {
        if (!m_data) 
        {
            allocate(); 
        }
        
        new(m_data) T(data); 
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
            ::operator delete(m_data, sizeof(T), std::align_val_t(alignof(T))); m_data = nullptr;
        }
    }

public:

    [[nodiscard]] auto empty   (      ) const { return !m_data; }
    [[nodiscard]] auto value   (      ) const { return *m_data; }
    [[nodiscard]] auto value_or(T data) const
    { 
        return m_data ? *m_data : data; 
    }

private:

    T * m_data = nullptr;
}; 

//  ================================================================================================

int main()
{
    Optional < int > optional_1, optional_2(2);

//  -----------------------------------------------------------

    assert( optional_1.empty() && optional_1.value_or(0) == 0);
    assert(!optional_2.empty() && optional_2.value_or(0) == 2);

//  -----------------------------------------------------------
    
    Optional < int > optional_3(optional_2);

    Optional < int > optional_4(std::move(optional_3));

    optional_3 = optional_2; 
    
    optional_4 = std::move(optional_3);

    optional_4 = 4;

//  -----------------------------------------------------------

    assert( optional_3.empty() && optional_3.value_or(0) == 0);
    assert(!optional_4.empty() && optional_4.value_or(0) == 4);
}