#include <cstddef>
#include <ios>
#include <iostream>
#include <ostream>

//////////////////////////////////////////////////////////////////////////

struct Formatter 
{ 
    std::size_t precision = 0; 
};

//////////////////////////////////////////////////////////////////////////

auto & operator<<(std::ostream & stream, const Formatter & formatter)
{
    stream.precision(formatter.precision);

    stream.setf(std::ios_base::fixed);

    stream.setf(std::ios_base::showpos);
    
    return stream;
}

//////////////////////////////////////////////////////////////////////////

template < typename T > class Helper 
{ 
public:

    explicit Helper(const T & data) : m_data(data) {}

//  ----------------------------------------------------------------------

    friend auto & operator<<(std::ostream & stream, const Helper & helper)
    {
        return stream << "test : arg = " << helper.m_data << '\n';
    }

private:

    const T & m_data;
};

//////////////////////////////////////////////////////////////////////////

template < typename ... Ts > void test(Ts ... args)
{
    (std::cout << ... << Helper(args));
}

//////////////////////////////////////////////////////////////////////////

int main()
{
    auto exceptions = std::cin.exceptions();

    std::cin.exceptions(std::ios::eofbit | std::ios::badbit);

    try
    {
        std::cout << "main : enter 1 or more integers and 1 non-integer : \n";
        
        int x; while (std::cin >> x);

        if (std::cin.fail()) 
        {
            std::cin.clear(); char c; std::cin >> c;
        }
    }
    catch (const std::ios_base::failure & exception)
    {
        std::cerr << "main : " << exception.what() << '\n';
    }

    std::cin.clear();
    
    std::cin.exceptions(exceptions);

//  -------------------------------------------------------------------

    auto flags = std::cout.flags();

    auto x = 1.0, y = 2.0;

    std::cout << "main : x = " << Formatter(3) << x << '\n';
    std::cout << "main : y = " << Formatter(6) << y << '\n';

    std::cout.flags(flags);

//  -------------------------------------------------------------------

    test(1, 2, 3);
}