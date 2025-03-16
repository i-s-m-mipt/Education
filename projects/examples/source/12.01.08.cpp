#include <bit>
#include <cassert>
#include <string>

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////

template < typename T1, typename T2 > auto distance(T1 * ptr_1, T2 * ptr_2)
{
    return 
    (
        std::bit_cast < std::byte * > (ptr_1) - 
        
        std::bit_cast < std::byte * > (ptr_2)
    );
}

///////////////////////////////////////////////////////////////////////////

int main()
{
    std::string string_1(15, 'a');
    
    std::string string_2(16, 'a');

//  -----------------------------------------------------

    assert(distance(&string_1.front(), &string_1) == 16);

    assert(distance(&string_2.front(), &string_2) != 16);
}