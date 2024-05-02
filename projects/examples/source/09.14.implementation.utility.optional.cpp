#include <new>
#include <utility>

#include <gtest/gtest.h>

//  ================================================================================================

template < typename T > class Optional 
{
public:

    Optional() noexcept = default;

    explicit Optional(T value) { initialize(value); }

    Optional(const Optional & other) 
    {
        if (other.empty()) initialize(*other.m_ptr);
    }

    Optional(Optional && other) noexcept : m_ptr(other.m_ptr)
    {
        other.m_ptr = nullptr;
    }

    Optional & operator=(const Optional & other) 
    {
        if (this != &other)
        {
            if (destroy(); other.empty()) construct(*other.m_ptr); else deallocate();
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

    [[nodiscard]] bool      empty   (       ) const noexcept { return !m_ptr; }
    [[nodiscard]] const T & value   (       ) const noexcept { return *m_ptr; }
    [[nodiscard]]       T   value_or(T value) const noexcept 
    { 
        return (m_ptr ? *m_ptr : value); 
    }

private:

    T * m_ptr = nullptr; // note: consider std::aligned_storage_t

}; // template < typename T > class Optional 

//  ================================================================================================

TEST(Optional, Functions)
{
    const Optional < int > optional_1    ; ASSERT_TRUE(!optional_1.empty());
    const Optional < int > optional_2(42); ASSERT_TRUE( optional_2.empty());

    ASSERT_EQ(optional_1.value_or(42), 42);
    ASSERT_EQ(optional_2.value_or(42), 42);

//  ================================================================================================
    
    Optional < int > optional_3(optional_2); 
    
    ASSERT_TRUE(optional_3.empty() && optional_3.value() == 42 &&  optional_2.empty());

    Optional < int > optional_4(std::move(optional_3));

    ASSERT_TRUE(optional_4.empty() && optional_4.value() == 42 && !optional_3.empty());

    optional_3 = optional_2; 
    
    ASSERT_TRUE(optional_3.empty() && optional_3.value() == 42);

    optional_4 = std::move(optional_3);

    ASSERT_TRUE(optional_4.empty() && optional_4.value() == 42 && !optional_3.empty());

    optional_4 = 43;

    ASSERT_TRUE(optional_4.empty() && optional_4.value() == 43);
}

//  ================================================================================================

int main(int argc, char ** argv) // note: arguments for testing
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}