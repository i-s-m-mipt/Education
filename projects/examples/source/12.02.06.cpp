/////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto string = "aaaaa 12345 AAAAA 12345"s;

//  ---------------------------------------------------------------------------------
        
    auto begin = std::cbegin(string);

//  ---------------------------------------------------------------------------------

    std::regex pattern(R"([a-z]{5})", std::regex_constants::icase);

//  ---------------------------------------------------------------------------------

    std::vector < std::string > strings;

//  ---------------------------------------------------------------------------------

    auto lambda = [&strings](auto const & matches){ strings.push_back(matches[0]); };

//  ---------------------------------------------------------------------------------

    std::ranges::for_each
    (
        std::sregex_iterator(begin, std::cend(string), pattern), 

        std::sregex_iterator(), lambda
    );

//  ---------------------------------------------------------------------------------

    assert(strings == std::vector < std::string > ({ "aaaaa", "AAAAA" }));
}

/////////////////////////////////////////////////////////////////////////////////////