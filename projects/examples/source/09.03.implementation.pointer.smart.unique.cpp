#include <cassert>
#include <cstddef>
#include <type_traits>
#include <utility>

#include <boost/noncopyable.hpp>

// =================================================================================================

template < typename T > class Unique : private boost::noncopyable
{
public:

    Unique() noexcept = default;

    explicit Unique(T * data) noexcept : m_data(data) {} // good: explicit
        
    Unique(Unique && other) noexcept : Unique() { swap(other); }

   ~Unique() noexcept { reset(); }

public:

    Unique & operator=(Unique && other) noexcept
    { 
        reset(other.release()); return *this;
    }

public:
        
    void swap(Unique & other) noexcept
    { 
        using std::swap; // good: enable argument-dependent lookup

        swap(m_data, other.m_data); 
    }

    [[nodiscard]] T * release() noexcept
    {
        return std::exchange(m_data, nullptr);
    }

    void reset(T * ptr = nullptr) noexcept 
    {
        delete std::exchange(m_data, ptr); // note: consider custom deleter
    }

public:

    [[nodiscard]] T & operator*() const noexcept { return *m_data; }
     
private:

    T * m_data = nullptr;

}; // template < typename T > class Unique : private boost::noncopyable

// =================================================================================================

template < typename T > inline void swap(Unique < T > & x, Unique < T > & y) noexcept
{
    x.swap(y);
}

// =================================================================================================

template < typename T, typename ... Ts > [[nodiscard]] inline Unique < T > make_unique(Ts && ... args)
{
    return Unique < T > (new T(std::forward < Ts > (args)...)); 
}

// =================================================================================================

int main()
{
    auto unique_1 = make_unique < const int > (42);
    auto unique_2 = make_unique < const int > (43);

    unique_2 = std::move(unique_1);

    assert(*unique_2 == 42);

    return 0;
}