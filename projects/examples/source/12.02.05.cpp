#include <cassert>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

using namespace std::literals;

//////////////////////////////////////////////////////////////////////////

// support : Boost.Tokenizer

//////////////////////////////////////////////////////////////////////////

int main()
{
    auto string = "aaaaa 12345 AAAAA 12345"s;
        
    auto begin = std::cbegin(string);

    std::smatch matches;
        
    std::regex pattern(R"([a-z]{5})", std::regex_constants::icase);

    std::vector < std::string > strings;

//  ----------------------------------------------------------------------

    while (std::regex_search(begin, std::cend(string), matches, pattern))
    {
        strings.push_back(matches[0]);

        begin = matches.suffix().first;
    }

//  ----------------------------------------------------------------------

    assert(strings == std::vector < std::string > ({ "aaaaa", "AAAAA" }));
}