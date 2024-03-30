#include <iostream>
#include <ostream>

// =================================================================================================

template < typename ... Types > void print_v1(const Types & ... args)
{
    (std::cout << ... << args) << std::endl; // note: fold expression with no spaces
}

// =================================================================================================

template < typename T > class Spaced
{
public:

    explicit Spaced(const T & reference) noexcept : m_reference(reference) {}

    friend std::ostream & operator<<(std::ostream & stream, Spaced < T > spaced)
    {
        return (stream << spaced.m_reference << ' ');
    }

private:

    const T & m_reference;

}; // template < typename T > class Spaced

// =================================================================================================

template < typename ... Types > void print_v2(const Types & ... args)
{
    (std::cout << ... << Spaced(args)) << std::endl; // note: fold expression with spaces
}

// =================================================================================================

int main()
{
    print_v1('a', 42, 3.14);
    print_v2('a', 42, 3.14);

    return 0;
}