#include <cassert>
#include <format>
#include <iomanip>
#include <sstream>

int main()
{
	std::stringstream stream;

    stream << std::showbase;

	stream << std::format("{:_>#8o}", 255);

	assert(stream.str() == "____0377");

//  ================================================================================================

	stream.seekp(0);

	stream << std::format("{:_>#8x}", 255);

	assert(stream.str() == "____0xff");

//  ================================================================================================

    for (char c; stream.get(c); )
    {
        if (c == '0')
        {
            stream.unget(); int x; stream >> std::hex >> x; assert(x == 255);
        }
    }

    assert(stream.eof());
}