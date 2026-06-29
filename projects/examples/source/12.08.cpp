/////////////////////////////////////////////////////////

// chapter : Characters

/////////////////////////////////////////////////////////

// content : Small Strings Optimization (SSO)

/////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <string>

/////////////////////////////////////////////////////////

auto distance(auto * x, auto * y)
{
    return
    (
        reinterpret_cast < std::byte * > (x) -

        reinterpret_cast < std::byte * > (y)
    );
}

/////////////////////////////////////////////////////////

int main()
{
    std::string string_1(15, 'a');

    std::string string_2(16, 'a');

//  -----------------------------------------------------

    static_assert(sizeof(std::string) == 32);

//  -----------------------------------------------------

    assert(distance(&string_1.front(), &string_1) == 16);

    assert(distance(&string_2.front(), &string_2) != 16);
}

/////////////////////////////////////////////////////////