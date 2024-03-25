#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

using namespace std::literals;

[[nodiscard]] inline bool match_identifier(const std::string & string)
{
	return std::regex_match(string, std::regex(R"([_[:alpha:]]\w*)")); // good: raw string
}

[[nodiscard]] inline std::smatch search_post_code(const std::string & string)
{
    std::smatch matches; // note: matches of type std::string, including groups
    
    std::regex_search(string, matches, std::regex(R"(\w{2}\d{5}(-\d{4})?)")); // good: raw string

    return matches;
}

[[nodiscard]] inline std::string replace_substring(const std::string & string)
{
    return std::regex_replace(string, std::regex(R"(\b(sub)([^ ]*))"), R"(sub-$2)"); // good: raw string
}

int main()
{
	assert(match_identifier("hello")         );
	assert(match_identifier("12345") == false); // note: invalid character (first)
	assert(match_identifier("_name")         );
	assert(match_identifier("_3.14") == false); // note: invalid character (third)
    assert(match_identifier("A1234")         );

    assert(search_post_code("_NY12345______")[0] == "NY12345"     );
    assert(search_post_code("_NY1234506789_")[0] == "NY12345"     );
    assert(search_post_code("_NY12345-6789_")[0] == "NY12345-6789");
    assert(search_post_code("_NY12345-6789_")[1] ==        "-6789"); // note: matched group

    assert(std::empty(search_post_code("_$1$2$3$4$_")));
    assert(std::empty(search_post_code("NY1234-6789")));

    const auto data = "AAA123BBB456CCC789"s; 

    std::smatch matches;
    
    const std::regex pattern(R"(\d{3})"); // good: raw string

    for (auto begin = std::cbegin(data); std::regex_search(begin, std::cend(data), matches, pattern); begin = matches.suffix().first)
    {
        std::cout << matches[0] << ' ';
    }

    std::cout << std::endl;

    {
        const std::sregex_iterator begin(std::begin(data), std::cend(data), pattern), end;

	    std::ranges::for_each(begin, end, [](const auto & matches){ std::cout << matches[0] << ' '; });

        std::cout << std::endl;
    }

    {
        const std::sregex_token_iterator begin(std::begin(data), std::cend(data), pattern, { 0 }), end;

        std::ranges::for_each(begin, end, [](const auto & match){ std::cout << match << ' '; });

        std::cout << std::endl;
    }

    {
        const std::sregex_token_iterator begin(std::begin(data), std::cend(data), pattern, { -1 }), end;

        std::ranges::for_each(begin, end, [](const auto & match){ std::cout << match << ' '; });

        std::cout << std::endl;
    }

    assert(replace_substring("subsequence in the substring") == "sub-sequence in the sub-string");

    return 0;
}