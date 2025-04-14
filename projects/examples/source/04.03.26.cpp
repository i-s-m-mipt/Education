/////////////////////////////////////////////////////////////////

#include <cassert>
#include <string>
#include <tuple>

/////////////////////////////////////////////////////////////////

using namespace std::literals;

/////////////////////////////////////////////////////////////////

int main()
{
    auto tuple = std::make_tuple(1, "aaaaa"s);

//  -------------------------------------------------------------

	static_assert(std::tuple_size_v < decltype(tuple) > == 2);

//  -------------------------------------------------------------

    assert(std::get < 0 > (tuple) == 1);

//  -------------------------------------------------------------

    auto x = 0;

//  -------------------------------------------------------------
        
    std::tie(x, std::ignore) = tuple;

//  -------------------------------------------------------------
        
    assert(x == 1);

//  -------------------------------------------------------------

    auto const & [y, string] = tuple; // support : cppinsights.io

//  -------------------------------------------------------------

    assert(y == 1 && string == "aaaaa");
}

/////////////////////////////////////////////////////////////////