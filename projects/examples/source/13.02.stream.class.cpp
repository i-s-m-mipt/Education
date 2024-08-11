#include <exception>
#include <iostream>
#include <ostream>
#include <stdexcept>

//  ================================================================================================

struct Formatter { std::size_t precision{}; };

//  ================================================================================================

inline std::ostream & operator<<(std::ostream & stream, Formatter f)
{
    stream.setf(std::ios_base::showpos);
    stream.setf(std::ios_base::fixed  );

    stream.precision(f.precision);
    
    return stream;
}

//  ================================================================================================

template < typename ... Ts > void print_v1(const Ts & ... args)
{
    (std::cout << ... << args) << std::endl;
}

//  ================================================================================================

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

//  ================================================================================================

template < typename ... Ts > void print_v2(const Ts & ... args)
{
    (std::cout << ... << Spaced(args)) << std::endl;
}

//  ================================================================================================

int main()
{
    const auto old_exceptions = std::cin.exceptions();

    std::cin.exceptions(std::ios::eofbit | std::ios::badbit);

    try
    {
        std::cout << "Enter some integers: "; int x{}; for (; std::cin >> x; );

        if (std::cin.fail()) 
        {
            std::cin.clear(); char c{}; std::cin >> c;

            std::cout << "Invalid character: " << c << std::endl;
        }
    }
    catch(const std::ios_base::failure & exception)
    {
        std::cerr << exception.what() << '\n';

        std::cin.clear();
    }
    
    std::cin.exceptions(old_exceptions);

//  ================================================================================================

    std::cout << Formatter { 6 } << 3.14 << std::endl;
    std::cout <<                    2.72 << std::endl;

//  ================================================================================================

    print_v1('a', 42, 3.14);
    print_v2('a', 42, 3.14);

    return 0;
}