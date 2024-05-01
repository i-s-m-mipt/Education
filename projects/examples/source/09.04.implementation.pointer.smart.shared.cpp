#include <cassert>
#include <cstddef>
#include <type_traits>
#include <utility>

#include <boost/noncopyable.hpp>

//  ================================================================================================

namespace detail
{
    class RCCB_base : private boost::noncopyable // note: non-template class, no custom deleters support
    {
    protected:

        RCCB_base() noexcept = default; // note: available from derived constructors only

        virtual ~RCCB_base() noexcept = default; // note: really polymorphic base class?

    public:

        void create_reference() noexcept { ++m_counter; }
        void remove_reference() noexcept 
        { 
            if (--m_counter == 0) clear(); 
        }

    private:

        virtual void clear() noexcept = 0; // note: NVI idiom

    private:

        std::size_t m_counter = 0; // note: consider std::atomic < std::size_t > for threadsafe version

    }; // class RCCB_base : private boost::noncopyable

} // namespace detail

//  ================================================================================================

namespace detail
{
    template < typename T > class RCCB : public RCCB_base
    {
    public:

        explicit RCCB(T * data) noexcept : m_data(data) // good: explicit
        {
            create_reference();
        }

    private:

        void clear() noexcept override
        {
            delete m_data; delete this; // note: other implementation required in case of make_shared
        }

    private:

        T * m_data = nullptr; // note: note pointer but object in case of make_shared

    }; // template < typename T > class RCCB : public RCCB_base

} // namespace detail

//  ================================================================================================

template < typename T > class Shared
{
public:

    Shared() noexcept = default;

    explicit Shared(T * data) : m_data(data)
    {
        try_make_rccb();
    }

    Shared(const Shared < T > & other) noexcept : m_data(other.m_data), m_rccb(other.m_rccb)
    {
        if (m_rccb) m_rccb->create_reference();
    }

    Shared(Shared < T > && other) noexcept : m_data(other.m_data), m_rccb(other.m_rccb)
    {
        other.m_data = nullptr;
        other.m_rccb = nullptr;
    }

    Shared & operator=(const Shared & other) noexcept
    {
        Shared(other).swap(*this); return *this;
    }

    Shared & operator=(Shared && other) noexcept
    {
        Shared(std::move(other)).swap(*this); return *this;
    }

   ~Shared() noexcept { if (m_rccb) m_rccb->remove_reference(); }

public:

    void swap(Shared & other) noexcept
    {
        using std::swap; // good: enable argument-dependent lookup

        swap(m_data, other.m_data);
        swap(m_rccb, other.m_rccb);
    }

public:

    [[nodiscard]] T & operator*() const noexcept { return *m_data; }

private:

    void try_make_rccb()
    {
        try { m_rccb = new detail::RCCB < T > (m_data); } catch (...) { delete m_data; }
    }

private:

    T * m_data = nullptr; detail::RCCB_base * m_rccb = nullptr;

}; // template < typename T > class Shared

//  ================================================================================================

template < typename T > inline void swap(Shared < T > & x, Shared < T > & y) noexcept
{
    x.swap(y);
}

//  ================================================================================================

template < typename T, typename ... Ts > [[nodiscard]] inline Shared < T > make_shared(Ts && ... args)
{
    // note: another RCCB required, combining control block and object in one allocation
}

//  ================================================================================================

int main()
{
    Shared < const int > shared_1(new const auto(42));
    Shared < const int > shared_2(new const auto(43));

    shared_2 = shared_1;

    assert(*shared_1 == 42);
    assert(*shared_2 == 42);

    return 0;
}