#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>

int main()
{
	std::stringstream stream;

    stream << std::showbase;

	stream << std::setw(8) << std::right << std::setfill('_') << std::oct << 42;

	assert(stream.str() == "_____052");

//  ================================================================================================

	stream.seekp(0);

	stream << std::setw(8) << std::right << std::setfill('_') << std::hex << 42;

	assert(stream.str() == "____0x2a");

//  ================================================================================================

    for (char c{}; stream.get(c); ) // note: consider calculator implementation
    {
        if (c == '0')
        {
            stream.unget(); int x{}; stream >> std::hex >> x; assert(x == 42);
        }
    }

    assert(stream.eof()); // note: all characters from stream processed successfully

	return 0;
}