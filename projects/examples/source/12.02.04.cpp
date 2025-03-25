#include <cassert>
#include <regex>
#include <string>

///////////////////////////////////////////////////////////////////////

auto test(const std::string & string)
{
    std::regex regex(R"(\b([a-z])([^\s]+))"); // support : regex101.com

    auto format = "$1-$2";

    return std::regex_replace(string, regex, format);
}

///////////////////////////////////////////////////////////////////////

int main()
{
    assert(test("aaaaa 12345") == "a-aaaa 12345");
}