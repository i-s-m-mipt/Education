/////////////////////////////////////////////////////////////////////////////

// chapter : Debugging and Profiling

/////////////////////////////////////////////////////////////////////////////

// section : Wrapping Error Codes

/////////////////////////////////////////////////////////////////////////////

// content : Wrappers std::expected and std::unexpected

/////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <expected>
#include <string>

/////////////////////////////////////////////////////////////////////////////

int main()
{
    std::expected < int, std::string > expected_1 = 1;

    std::expected < int, std::string > expected_2 = std::unexpected("aaaaa");

//  -------------------------------------------------------------------------

    assert(expected_1.has_value() == 1 && expected_1.value_or(2) == 1);

    assert(expected_2.has_value() == 0 && expected_2.value_or(3) == 3);

//  -------------------------------------------------------------------------

    assert(expected_1.error_or("bbbbb") == "bbbbb");

    assert(expected_2.error_or("bbbbb") == "aaaaa");
}

/////////////////////////////////////////////////////////////////////////////