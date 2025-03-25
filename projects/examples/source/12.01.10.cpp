#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

using namespace std::literals;

///////////////////////////////////////////////////////////////////////

int main()
{
    [[maybe_unused]] char string_1[5]{ 'a', 'a', 'a', 'a', 'a'       };

    [[maybe_unused]] char string_2[6]{ 'a', 'a', 'a', 'a', 'a', '\0' };
        
    [[maybe_unused]] char string_3[6] = "aaaaa";

    [[maybe_unused]] auto string_4    = "aaaaa";

//  -------------------------------------------------------------------

//  assert(std::strlen(string_1) == 5); // error

    assert(std::strlen(string_2) == 5);

//  -------------------------------------------------------------------

    assert(std::strlen("aaaaa"s.c_str()) == 5);

//  -------------------------------------------------------------------

    char array[1'000]{};

//  -------------------------------------------------------------------

    std::stringstream stream_1("aaaaa");

    std::stringstream stream_2;
        
//  -------------------------------------------------------------------
    
    stream_1.getline(array, std::size(array));

    stream_2 << array;

//  -------------------------------------------------------------------

    assert(stream_2.str() == stream_1.str());
}