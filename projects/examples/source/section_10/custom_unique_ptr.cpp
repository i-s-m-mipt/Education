#include <cstddef>
#include <type_traits>
#include <utility>

namespace stdx // note: extended std namespace
{
    template < typename T > class unique_ptr
    {
    public:

        constexpr unique_ptr() noexcept = default;

        constexpr explicit unique_ptr(T * data) noexcept : m_data(data) {} // good: explicit

        constexpr unique_ptr(std::nullptr_t) noexcept {} // note: version for nullptr literal

        constexpr unique_ptr(const unique_ptr &) noexcept = delete;
        
        constexpr unique_ptr(unique_ptr && other) noexcept : unique_ptr() { swap(other); }

        template < typename U > constexpr unique_ptr(unique_ptr < U > && other) noexcept
        {
            unique_ptr < T > t(other.release()); swap(t); // note: used for base-derived
        }

        constexpr ~unique_ptr() noexcept { reset(); }

    public:

        constexpr unique_ptr & operator=(const unique_ptr &) noexcept = delete;

        constexpr unique_ptr & operator=(unique_ptr && other) noexcept
        { 
            reset(other.release()); return *this;
        }

        template < typename U > constexpr unique_ptr & operator=(unique_ptr < U > && other) noexcept
        {
            unique_ptr < T > t(other.release()); swap(t); return *this; // note: used for base-derived
        }

        constexpr unique_ptr & operator=(std::nullptr_t) noexcept // note: version for nullptr literal
        { 
            reset(); return *this; 
        }

        constexpr explicit operator bool() const noexcept { return m_data; }

    public:
        
        constexpr void swap(unique_ptr & other) noexcept
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

        [[nodiscard]] T *        get() const noexcept { return  m_data; }
        [[nodiscard]] T * operator->() const noexcept { return  m_data; }
        [[nodiscard]] T & operator* () const noexcept { return *m_data; }
     
    private:

        T * m_data = nullptr;

    }; // template < typename T > class unique_ptr

    template < typename T > constexpr void swap(unique_ptr < T > & lhs, unique_ptr < T > & rhs)
    {
        lhs.swap(rhs);
    }

} // namespace stdx

class B            {};
class D : public B {};

int main()
{
    stdx::unique_ptr < B > b_ptr(new B);
    stdx::unique_ptr < D > d_ptr(new D);

    b_ptr = std::move(d_ptr);

    return 0;
}