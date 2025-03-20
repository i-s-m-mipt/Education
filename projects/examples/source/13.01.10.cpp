#include <cassert>
#include <sstream>
#include <string>

/////////////////////////////////////////////

int main()
{
	std::stringstream stream_1("aaaaa");

	std::stringstream stream_2;

//  -----------------------------------------

    std::string string;

//  -----------------------------------------
	
    stream_1 >> string;

    stream_2 << string;
	
//  -----------------------------------------
	
	assert(stream_2.str() == stream_1.str());
}