#include <cassert>
#include <new>
#include <utility>

//////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Optional 
{
public:

    Optional() = default;

    Optional(T x) 
    { 
        initialize(x);
    }

//  ------------------------------------------------------------------------------------------

    Optional(const Optional & other) 
    {
        if (other.m_data) 
        {
            initialize(*other.m_data);
        }
    }

    Optional(Optional && other) : m_data(other.m_data)
    {
        other.m_data = nullptr;
    }

//  ------------------------------------------------------------------------------------------

    auto & operator=(const Optional & other) 
    {
        if (this != &other)
        {
            destroy();
            
            if (other.m_data) 
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
            uninitialize();
            
            m_data = other.m_data;
            
            other.m_data = nullptr;
		}

		return *this;
    } 

    auto & operator=(T x) 
    {
        destroy();
        
        construct(x);
        
        return *this;
    }

//  ------------------------------------------------------------------------------------------

   ~Optional() 
    { 
        uninitialize();
    }

private:

    void initialize(T x) 
    { 
        allocate();
        
        construct(x);
    }

    void uninitialize() 
    { 
        destroy();
        
        deallocate();
    }

//  ------------------------------------------------------------------------------------------

    void allocate() 
    { 
        m_data = static_cast < T * > (operator new(sizeof(T), std::align_val_t(s_alignment)));
    }

    void deallocate()
    { 
        if (m_data)
        {
            operator delete(m_data, sizeof(T), std::align_val_t(s_alignment));
            
            m_data = nullptr;
        }
    }

//  ------------------------------------------------------------------------------------------

    void construct(T x) 
    {
        if (!m_data) 
        {
            allocate();
        }
        
        new (m_data) T(x);
    }

    void destroy() 
    { 
        if (m_data) 
        {
            m_data->~T();
        } 
    }

//  ------------------------------------------------------------------------------------------

    T * m_data = nullptr;

//  ------------------------------------------------------------------------------------------

    static inline auto s_alignment = alignof(T);
};

//////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Optional < int > optional_1;
    
    Optional < int > optional_2 = 2;

//  ----------------------------------------------------

    Optional < int > optional_3 = optional_2;

                     optional_3 = optional_2;

//  ----------------------------------------------------

    Optional < int > optional_4 = std::move(optional_3);

                     optional_4 = std::move(optional_3);

                     optional_4 = 4;  
}