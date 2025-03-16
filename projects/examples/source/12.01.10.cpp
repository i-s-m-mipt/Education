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

    char array[1'000]{};

//  -------------------------------------------------------------------

    std::istringstream istream("aaaaa");

    std::ostringstream ostream;
        
//  -------------------------------------------------------------------
    
    istream.getline(array, std::size(array));

    ostream << array;

//  -------------------------------------------------------------------

    assert(ostream.str() == istream.str());
}