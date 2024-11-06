#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>

int main()
{
	std::stringstream stream;

    stream << std::showbase;

	stream << std::setw(8) << std::setfill('_') << std::right << std::oct << 42;

	assert(stream.str() == "_____052");

//  ================================================================================================

	stream.seekp(0);

	stream << std::setw(8) << std::setfill('_') << std::right << std::hex << 42;

	assert(stream.str() == "____0x2a");

//  ================================================================================================

    for (char c; stream.get(c); )
    {
        if (c == '0')
        {
            stream.unget(); int x; stream >> std::hex >> x; assert(x == 42);
        }
    }

    assert(stream.eof());
}