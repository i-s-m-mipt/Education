///////////////////////////////////////////////////////////////////

#include <bit>
#include <cassert>
#include <cstddef>
#include <string>

///////////////////////////////////////////////////////////////////

template < typename T1, typename T2 > auto distance(T1 * x, T2 * y)
{
    return 
    (
        std::bit_cast < std::byte * > (x) - 
        
        std::bit_cast < std::byte * > (y)
    );
}

///////////////////////////////////////////////////////////////////

int main()
{
    std::string string_1(15, 'a');
    
    std::string string_2(16, 'a');

//  -----------------------------------------------------

    assert(distance(&string_1.front(), &string_1) == 16);

    assert(distance(&string_2.front(), &string_2) != 16);
}

///////////////////////////////////////////////////////////////////