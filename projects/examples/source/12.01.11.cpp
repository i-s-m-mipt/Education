#include <iostream>
#include <iterator>
#include <string>
#include <string_view>

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////////////

void test(std::string_view view) 
{
    std::cout << "test : view = " << view << '\n';
}

///////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto string = "aaaaa"s; // support : compiler-explorer.com

//  -------------------------------------------------------------------------------

    [[maybe_unused]] std::string_view view_1(std::data(string), std::size(string));

    [[maybe_unused]] std::string_view view_2 = "aaaaa";

//  [[maybe_unused]] std::string_view view_3 = "aaaaa"s; // bad

//  -------------------------------------------------------------------------------

    [[maybe_unused]] auto view_4 = "aaaaa"sv;

//  -------------------------------------------------------------------------------
    
    test(string);
}