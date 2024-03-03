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
        if (other.has_value()) 
        {
            initialize(*other.m_ptr);
        }
    }

    Optional(Optional && other) noexcept : m_ptr(other.m_ptr)
    {
        other.m_ptr = nullptr;
    }

    Optional & operator=(const Optional & other) 
    {
        if (this != &other)
        {
            if (destroy(); other.has_value()) 
            {
                construct(*other.m_ptr);
            } 
            else deallocate();
        }

        return *this;
    }

    Optional & operator=(Optional && other) noexcept
    {
        if (this != &other)
		{
            uninitialize();

            m_ptr = other.m_ptr;

            other.m_ptr = nullptr;
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
        ::operator delete(m_ptr, std::align_val_t(alignof(T))); 
        
        m_ptr = nullptr;
    }

public:

    [[nodiscard]] bool  has_value() const noexcept { return  m_ptr; }

    [[nodiscard]]       T & value()       noexcept { return *m_ptr; }
    [[nodiscard]] const T & value() const noexcept { return *m_ptr; }

    [[nodiscard]] T value_or(T value) const noexcept 
    { 
        return (m_ptr ? *m_ptr : value); 
    }

private:

    T * m_ptr = nullptr;

}; // template < typename T > class Optional 

int main()
{
    Optional < int > o1; assert(!o1.has_value());

    assert(o1.value_or(42) == 42);

    Optional < int > o2(42); assert(o2.has_value() && o2.value() == 42);
    Optional < int > o3(o2); assert(o3.has_value() && o3.value() == 42);

    Optional < int > o4(std::move(o3));

    assert(o4.has_value() && o4.value() == 42 && !o3.has_value());

    o3 = o2; 
    
    assert(o3.has_value() && o3.value() == 42);

    o4 = std::move(o3);

    assert(o4.has_value() && o4.value() == 42 && !o3.has_value());

    o4 = 43;

    assert(o4.has_value() && o4.value() == 43);

    return 0;
}