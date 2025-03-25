#include <algorithm>
#include <cassert>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

using namespace std::literals;

////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto string = "aaaaa 12345 AAAAA 12345"s;
        
    auto begin = std::cbegin(string);

    std::regex pattern(R"(([a-z]{1})([a-z]{4}))", std::regex_constants::icase);

    std::vector < std::string > strings;

    auto lambda = [&strings](const auto & match){ strings.push_back(match); };

//  --------------------------------------------------------------------------------

    std::ranges::for_each
    (
        std::sregex_token_iterator(begin, std::cend(string), pattern, { 0, 1 }),
            
        std::sregex_token_iterator(), lambda
    );

//  --------------------------------------------------------------------------------

    assert(strings == std::vector < std::string > ({ "a", "aaaaa", "A", "AAAAA" }));
}