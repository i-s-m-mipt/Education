#include <cassert>
#include <cstddef>
#include <ios>
#include <ostream>
#include <sstream>

////////////////////////////////////////////////////////////////////////////

struct Manipulator 
{ 
    std::size_t precision = 0;
};

////////////////////////////////////////////////////////////////////////////

auto & operator<<(std::ostream & stream, const Manipulator & manipulator)
{
    stream.precision(manipulator.precision);

    stream.setf(std::ios_base::fixed);
    
    return stream;
}

////////////////////////////////////////////////////////////////////////////

int main()
{
    assert((std::stringstream() << Manipulator(3) << 1.0).str() == "1.000");
}