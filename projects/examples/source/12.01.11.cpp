#include <iterator>
#include <string>
#include <string_view>

using namespace std::literals;

//////////////////////////////////////////////////////////////////

void test(std::string_view) {}

//////////////////////////////////////////////////////////////////

int main()
{
    test("aaaaa"s );
    
    test("aaaaa"sv);

//  --------------------------------------------------------------

    auto string = "aaaaa"s;

//  --------------------------------------------------------------

    std::string_view view_1(std::data(string), std::size(string));

//  std::string_view view_2 = "aaaaa"s; // bad

//  std::string_view view_3 = [](){ return "aaaaa"s; }(); // bad

//  --------------------------------------------------------------

//  string = "bbbbb"; // bad
}