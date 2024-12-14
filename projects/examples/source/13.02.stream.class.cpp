#include <cstddef>
#include <ios>
#include <iostream>
#include <ostream>

//  ================================================================================================

struct Formatter 
{ 
    std::size_t precision = 0; 
};

//  ================================================================================================

auto & operator<<(std::ostream & stream, const Formatter & formatter)
{
    stream.setf(std::ios_base::showpos);
    stream.setf(std::ios_base::fixed  );

    stream.precision(formatter.precision);
    
    return stream;
}

//  ================================================================================================

template < typename ... Ts > void print_v1(Ts ... args)
{
    (std::cout << ... << args) << std::endl;
}

//  ================================================================================================

template < typename T > struct Helper 
{ 
    const T & data; 
};

template < typename T > auto & operator<<(std::ostream & stream, const Helper < T > & helper)
{
    return stream << helper.data << ' ';
}

//  ================================================================================================

template < typename ... Ts > void print_v2(Ts ... args)
{
    (std::cout << ... << Helper(args)) << std::endl;
}

//  ================================================================================================

int main()
{
    auto exceptions = std::cin.exceptions();

    std::cin.exceptions(std::ios::eofbit | std::ios::badbit);

    try
    {
        std::cout << "Enter 1 or more integers : "; int x; for (; std::cin >> x; );

        if (std::cin.fail()) 
        {
            std::cin.clear(); char c; std::cin >> c;

            std::cout << "c = " << c << '\n';
        }
    }
    catch (const std::ios_base::failure & exception)
    {
        std::cerr << "main : " << exception.what() << '\n';
    }

    std::cin.clear();
    
    std::cin.exceptions(exceptions);

//  ================================================================================================

    auto x = 1.0, y = 2.0;

    std::cout << "x = " << Formatter(3) << x << '\n';
    std::cout << "y = " << Formatter(6) << y << '\n';

//  ================================================================================================

    print_v1('a', 1, 1.0);
    print_v2('a', 1, 1.0);
}