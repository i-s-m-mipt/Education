#include <cassert>
#include <format>
#include <iomanip>
#include <sstream>

/////////////////////////////////////////////////////////////

int main()
{
	std::stringstream stream;

	stream << std::format("{:_>#8o}", 255);

	assert(stream.str() == "____0377");

	stream.seekp(0);

	stream << std::format("{:_>#8x}", 255);

	assert(stream.str() == "____0xff");

    auto x = '\0';

    while (stream.get(x))
    {
        if (x == '0')
        {
            stream.unget(); 
            
            auto y = 0; stream >> std::hex >> y; assert(y == 255);
        }
    }

    assert(stream.eof());
}