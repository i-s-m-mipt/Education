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

    char c;

    while (stream.get(c))
    {
        if (c == '0')
        {
            stream.unget(); 
            
            auto x = 0; stream >> std::hex >> x; assert(x == 255);
        }
    }

    assert(stream.eof());
}