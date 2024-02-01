#include <cassert>
#include <cstddef>
#include <type_traits>
#include <utility>

class RCCB_base // note: non-template/polymorphic/copyable class, no custom deleters support
{
protected:

    RCCB_base() noexcept = default; // note: available from RCCB only

public:

    RCCB_base            (const RCCB_base &) = delete;
    RCCB_base & operator=(const RCCB_base &) = delete;

    void create_reference() noexcept { ++m_counter; }
    void remove_reference() noexcept 
    { 
        if (--m_counter == 0) clear(); 
    }

private:

    virtual void clear() noexcept = 0; // note: NVI idiom

private:

    std::size_t m_counter = 0; // note: consider std::atomic < std::size_t > for threadsafe version

}; // class RCCB_base

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

    T * m_data = nullptr;

}; // template < typename T > class RCCB : public RCCB_base

template < typename T > class Shared
{
public:

    Shared() noexcept = default;

    explicit Shared(T * data) noexcept : m_data(data)
    {
        try_make_rccb();
    }

    Shared(const Shared < T > &  other) noexcept : m_data(other.m_data), m_rccb(other.m_rccb)
    {
        if (m_rccb) m_rccb->create_reference();
    }

    Shared(      Shared < T > && other) noexcept : m_data(other.m_data), m_rccb(other.m_rccb)
    {
        other.m_data = nullptr;
        other.m_rccb = nullptr;
    }

    ~Shared() noexcept { if (m_rccb) m_rccb->remove_reference(); }

public:

    Shared & operator=(const Shared  & other) noexcept
    {
        Shared(other).swap(*this); return *this;
    }

    Shared & operator=(      Shared && other) noexcept
    {
        Shared(std::move(other)).swap(*this); return *this;
    }

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

    void try_make_rccb() noexcept
    {
        try { m_rccb = new RCCB < T > (m_data); } catch (...) { delete m_data; }
    }

private:

    T * m_data = nullptr; RCCB_base * m_rccb = nullptr;

}; // template < typename T > class Shared

template < typename T > void swap(Shared < T > & lhs, Shared < T > & rhs) noexcept
{
    lhs.swap(rhs);
}

int main()
{
    Shared < int > shared_1(new int(42));
    Shared < int > shared_2(new int(43));

    shared_2 = shared_1;

    assert(*shared_1 == 42);
    assert(*shared_2 == 42);

    return 0;
}