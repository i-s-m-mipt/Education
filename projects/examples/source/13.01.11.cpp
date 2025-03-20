#include <cassert>
#include <iterator>
#include <sstream>

//////////////////////////////////////////////////////////////

int main()
{
    std::stringstream stream_1("aaaaa");

    std::stringstream stream_2;

//  ----------------------------------------------------------

    std::istreambuf_iterator < char > iterator_1(stream_1);

	std::ostreambuf_iterator < char > iterator_2(stream_2);
    
//  ----------------------------------------------------------

	while (iterator_1 != std::istreambuf_iterator < char > ()) 
	{
		*iterator_2++ = *iterator_1++;
	}

//  ----------------------------------------------------------

	assert(stream_2.str() == stream_1.str());
}