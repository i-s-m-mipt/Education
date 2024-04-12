#include <cassert>
#include <new>
#include <utility>

template < typename T > class Optional 
{
public:

    Optional() noexcept = default;

    explicit Optional(T value) { initialize(value); }

    Optional(const Optional & other) 
    {
        if (other.has_value()) initialize(*other.m_ptr);
    }

    Optional(Optional && other) noexcept : m_ptr(other.m_ptr)
    {
        other.m_ptr = nullptr;
    }

    Optional & operator=(const Optional & other) 
    {
        if (this != &other)
        {
            if (destroy(); other.has_value()) construct(*other.m_ptr); else deallocate();
        }

        return *this;
    }

    Optional & operator=(Optional && other) noexcept
    {
        if (this != &other)
		{
            uninitialize(); m_ptr = other.m_ptr; other.m_ptr = nullptr;
		}

		return *this;
    } 

    Optional & operator=(T value) 
    {
        destroy(); construct(value); return *this;
    }

    ~Optional() noexcept { uninitialize(); }

private:

    void initialize(T value) { allocate(); construct(value); }

    void allocate() 
    { 
        m_ptr = static_cast < T * > (::operator new(sizeof(T), std::align_val_t(alignof(T)))); 
    }

    void construct(T value) 
    {
        if (!m_ptr) allocate(); 
        
        new(m_ptr) T(value); 
    }

    void uninitialize() { destroy(); deallocate(); }

    void destroy() noexcept { if (m_ptr) m_ptr->~T(); }

    void deallocate() noexcept
    { 
        ::operator delete(m_ptr, sizeof(T), std::align_val_t(alignof(T))); m_ptr = nullptr;
    }

public:

    [[nodiscard]] bool  has_value          () const noexcept { return  m_ptr; }

    [[nodiscard]]       T & value          ()       noexcept { return *m_ptr; }
    [[nodiscard]] const T & value          () const noexcept { return *m_ptr; }

    [[nodiscard]]       T   value_or(T value) const noexcept 
    { 
        return (m_ptr ? *m_ptr : value); 
    }

private:

    T * m_ptr = nullptr;

}; // template < typename T > class Optional 

int main()
{
    const Optional < int > optional_1    ; assert(!optional_1.has_value());
    const Optional < int > optional_2(42); assert( optional_2.has_value());

    assert(optional_1.value_or(42) == 42 && optional_2.value_or(42) == 42);
    
    Optional < int > optional_3(optional_2); 
    
    assert(optional_3.has_value() && optional_3.value() == 42 &&  optional_2.has_value());

    Optional < int > optional_4(std::move(optional_3));

    assert(optional_4.has_value() && optional_4.value() == 42 && !optional_3.has_value());

    optional_3 = optional_2; 
    
    assert(optional_3.has_value() && optional_3.value() == 42);

    optional_4 = std::move(optional_3);

    assert(optional_4.has_value() && optional_4.value() == 42 && !optional_3.has_value());

    optional_4 = 43;

    assert(optional_4.has_value() && optional_4.value() == 43);

    return 0;
}