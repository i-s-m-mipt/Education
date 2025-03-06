#include <cassert>
#include <optional>
#include <string>

/////////////////////////////////////////////////////////////////////////

int main()
{
    std::optional < int > optional_1 = 1;

    std::optional < int > optional_2 = std::nullopt;

//  ---------------------------------------------------------------------

    assert(optional_1.value_or(2) == 1);

    assert(optional_2.value_or(2) == 2);

//  ---------------------------------------------------------------------

    assert(std::make_optional < std::string > (5, 'a')->contains("aaa"));
}