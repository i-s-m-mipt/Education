/////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <expected>
#include <string>

/////////////////////////////////////////////////////////////////////////////

int main()
{
    std::expected < int, std::string > expexted_1 = 1;

    std::expected < int, std::string > expexted_2 = std::unexpected("aaaaa");

//  -------------------------------------------------------------------------

    assert(expexted_1.value_or(2) == 1);

    assert(expexted_2.value_or(3) == 3);

//  -------------------------------------------------------------------------

    assert(expexted_1.error_or("bbbbb") == "bbbbb");

    assert(expexted_2.error_or("bbbbb") == "aaaaa");
}

/////////////////////////////////////////////////////////////////////////////