#include <cstddef>
#include <type_traits>
#include <utility>

template < typename T > class Unique_Ptr
{
public:

    constexpr Unique_Ptr() noexcept = default;

    constexpr explicit Unique_Ptr(T * data) noexcept : m_data(data) {} // good: explicit

    constexpr Unique_Ptr(std::nullptr_t) noexcept {} // note: version for nullptr literal

    constexpr Unique_Ptr(const Unique_Ptr &) noexcept = delete;
        
    constexpr Unique_Ptr(Unique_Ptr && other) noexcept : Unique_Ptr() { swap(other); }

    template < typename U > constexpr Unique_Ptr(Unique_Ptr < U > && other) noexcept
    {
        Unique_Ptr < T > t(other.release()); swap(t); // note: used for base-derived
    }

    constexpr ~Unique_Ptr() noexcept { reset(); }

public:

    constexpr Unique_Ptr & operator=(const Unique_Ptr &) noexcept = delete;

    constexpr Unique_Ptr & operator=(Unique_Ptr && other) noexcept
    { 
        reset(other.release()); return *this;
    }

    template < typename U > constexpr Unique_Ptr & operator=(Unique_Ptr < U > && other) noexcept
    {
        Unique_Ptr < T > t(other.release()); swap(t); return *this; // note: used for base-derived
    }

    constexpr Unique_Ptr & operator=(std::nullptr_t) noexcept // note: version for nullptr literal
    { 
        reset(); return *this; 
    }

    constexpr explicit operator bool() const noexcept { return m_data; }

public:
        
    constexpr void swap(Unique_Ptr & other) noexcept
    { 
        using std::swap; // good: enable argument-dependent lookup

        swap(m_data, other.m_data); 
    }

    [[nodiscard]] constexpr T * release() noexcept
    {
        return std::exchange(m_data, nullptr);
    }

    constexpr void reset(T * ptr = nullptr) noexcept 
    {
        delete std::exchange(m_data, ptr); // note: consider custom deleter
    }

public:

    [[nodiscard]] constexpr T *        get() const noexcept { return  m_data; }
    [[nodiscard]] constexpr T * operator->() const noexcept { return  m_data; }
    [[nodiscard]] constexpr T & operator* () const noexcept { return *m_data; }
     
private:

    T * m_data = nullptr;

}; // template < typename T > class Unique_Ptr

template < typename T > constexpr void swap(Unique_Ptr < T > & lhs, Unique_Ptr < T > & rhs)
{
    lhs.swap(rhs);
}

class B            {};
class D : public B {};

int main()
{
    Unique_Ptr < B > b_ptr(new B);
    Unique_Ptr < D > d_ptr(new D);

    b_ptr = std::move(d_ptr);

    return 0;
}