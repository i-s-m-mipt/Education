#include <cassert>
#include <regex>
#include <string>

////////////////////////////////////////////////////////////////////////////

auto test(const std::string & string)
{
    std::smatch matches;

    std::regex regex(R"([a-z]{5}-\d{5}(-\d{5})?)"); // support: regex101.com
    
    std::regex_search(string, matches, regex);

    return matches;
}

////////////////////////////////////////////////////////////////////////////

int main()
{
    assert(test(" aaaaa-12345       ")[0] == "aaaaa-12345"      );

    assert(test(" aaaaa-12345-12345 ")[0] == "aaaaa-12345-12345");

    assert(test(" aaaaa-12345-12345 ")[1] ==            "-12345");
}