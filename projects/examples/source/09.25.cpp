///////////////////////////////////////////////////////////////////////////////////////////

// chapter : Memory Management

///////////////////////////////////////////////////////////////////////////////////////////

// section : Dynamic Memory

///////////////////////////////////////////////////////////////////////////////////////////

// content : Optionals
//
// content : Type std::align_val_t

///////////////////////////////////////////////////////////////////////////////////////////

#include <new>
#include <utility>

///////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Optional 
{
public :

    Optional() = default;

//  ---------------------------------------------------------------------------------------

    Optional(T x) 
    { 
        initialize(x);
    }

//  ---------------------------------------------------------------------------------------

    Optional(Optional const & other) 
    {
        if (other.m_x) 
        {
            initialize(*other.m_x);
        }
    }

//  ---------------------------------------------------------------------------------------

    Optional(Optional && other) : m_x(std::exchange(other.m_x, nullptr)) {}

//  ---------------------------------------------------------------------------------------

   ~Optional() 
    { 
        uninitialize();
    }

//  ---------------------------------------------------------------------------------------

    auto & operator=(Optional const & other) 
    {
        if (this != &other)
        {
            destroy();
            
            if (other.m_x) 
            {
                construct(*other.m_x);
            }
            else 
            {
                deallocate();
            }
        }

        return *this;
    }

//  ---------------------------------------------------------------------------------------

    auto & operator=(Optional && other)
    {
        if (this != &other)
		{
            uninitialize();

            m_x = std::exchange(other.m_x, nullptr);
		}

		return *this;
    }

//  ---------------------------------------------------------------------------------------

    auto & operator=(T x) 
    {
        destroy();
        
        construct(x);
        
        return *this;
    }

private :

    void initialize(T x) 
    { 
        allocate();
        
        construct(x);
    }

//  ---------------------------------------------------------------------------------------

    void uninitialize() 
    { 
        destroy();
        
        deallocate();
    }

//  ---------------------------------------------------------------------------------------

    void allocate() 
    { 
        m_x = static_cast < T * > (operator new(sizeof(T), std::align_val_t(s_alignment)));
    }

//  ---------------------------------------------------------------------------------------

    void deallocate()
    {
        operator delete(m_x, sizeof(T), std::align_val_t(s_alignment));
            
        m_x = nullptr;
    }

//  ---------------------------------------------------------------------------------------

    void construct(T x) 
    {
        if (!m_x) 
        {
            allocate();
        }
        
        new (m_x) T(x);
    }

//  ---------------------------------------------------------------------------------------

    void destroy() 
    { 
        if (m_x) 
        {
            m_x->~T();
        } 
    }

//  ---------------------------------------------------------------------------------------

    T * m_x = nullptr;

//  ---------------------------------------------------------------------------------------

    static inline auto s_alignment = alignof(T);
};

///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Optional < int > optional_1;
    
    Optional < int > optional_2 = 2;

    Optional < int > optional_3 = optional_2;

    Optional < int > optional_4 = std::move(optional_3);

//  ----------------------------------------------------

    optional_3 = optional_2;

    optional_4 = std::move(optional_3);

    optional_1 = 1;
}

///////////////////////////////////////////////////////////////////////////////////////////