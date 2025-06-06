/////////////////////////////////////////////////////////////////////////////

#include <array>
#include <cassert>
#include <cstring>
#include <span>
#include <spanstream>
#include <string>

/////////////////////////////////////////////////////////////////////////////

int main()
{
    std::array < char, 1'000 > array_1 = { 'a', 'a', 'a', 'a', 'a', '\0' };

    std::array < char, 1'000 > array_2 = {};

//  -------------------------------------------------------------------------

    std::spanstream stream_1(array_1);

    std::spanstream stream_2(array_2);

//  -------------------------------------------------------------------------

    std::string string;

//  -------------------------------------------------------------------------
	
    stream_1 >> string;

    stream_2 << string << '\0';

//  -------------------------------------------------------------------------

    assert(std::strcmp(stream_2.span().data(), stream_1.span().data()) == 0);
}

/////////////////////////////////////////////////////////////////////////////