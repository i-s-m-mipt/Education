#include <cstddef>
#include <ios>
#include <iostream>
#include <ostream>

/////////////////////////////////////////////////////////////////////////////////////////////

struct Manipulator 
{ 
    std::size_t precision = 0; 
};

/////////////////////////////////////////////////////////////////////////////////////////////

auto & operator<<(std::ostream & stream, const Manipulator & manipulator)
{
    stream.precision(manipulator.precision);

    stream.setf(std::ios_base::fixed);

    stream.setf(std::ios_base::showpos);
    
    return stream;
}

/////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > struct View 
{
    const T & data;
};

/////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > auto & operator<<(std::ostream & stream, const View < T > & view)
{
    return stream << "test : view.data = " << view.data << '\n';
}

/////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > void test(Ts ... xs)
{
    (std::cout << ... << View(xs));
}

/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        auto exceptions = std::cin.exceptions();

        std::cin.exceptions(std::ios::eofbit | std::ios::badbit);

        try
        {
            std::cout << "main : enter ints and non-int : ";
            
            auto x = 0; while (std::cin >> x);

            if (std::cin.fail()) 
            {
                std::cin.clear(); auto y = '\0'; std::cin >> y;
            }
        }
        catch (const std::ios_base::failure & exception)
        {
            std::cerr << "main : " << exception.what() << '\n';
        }

        std::cin.clear();
        
        std::cin.exceptions(exceptions);
    }
    
//  -------------------------------------------------------------

    {
        auto flags = std::cout.flags();

        auto x = 1.0, y = 2.0;

        std::cout << "main : x = " << Manipulator(3) << x << '\n';

        std::cout << "main : y = " << Manipulator(6) << y << '\n';

        std::cout.flags(flags);
    }

//  -------------------------------------------------------------

    {
        test(1, 2, 3);
    }
}