#include <exception>
#include <iostream>
#include <ostream>
#include <stdexcept>

struct Formatter { std::size_t precision{}; };

inline std::ostream & operator<<(std::ostream & stream, Formatter f)
{
    stream.setf(std::ios_base::showpos); // note: flag in the stream
    stream.setf(std::ios_base::fixed  ); // note: flag in the stream

    stream.precision(f.precision);
    
    return stream;
}

int main()
{
    const auto old_exceptions = std::cin.exceptions();

    std::cin.exceptions(std::ios::failbit | std::ios::badbit); // good: allow exceptions

    try
    {
        for (int x{}; std::cin >> x; ); // note: try enter any letter instead of numbers
    }
    catch(const std::ios_base::failure & exception)
    {
        std::cerr << exception.what() << '\n';

        if (std::cin.fail()) 
        {
            std::cin.clear(); char c{}; std::cin >> c; // note: make stream goodbit state

            std::cout << "invalid entered character: " << c << std::endl;
        }
    }
    
    std::cin.exceptions(old_exceptions);

    std::cout << Formatter(6) << 3.14 << std::endl;
    std::cout <<                 2.72 << std::endl; // note: flags are preserved

    return 0;
}