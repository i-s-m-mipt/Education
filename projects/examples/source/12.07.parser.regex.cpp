#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

using namespace std::literals;

//  ================================================================================================

auto match(const std::string & string)
{
	return std::regex_match(string, std::regex(R"([_[:alpha:]]\w*)"));
}

//  ================================================================================================

auto search(const std::string & string)
{
    std::smatch matches;
    
    std::regex_search(string, matches, std::regex(R"([a-z]{2}\d{5}(-\d{4})?)"));

    return matches;
}

//  ================================================================================================

auto replace(const std::string & string)
{
    return std::regex_replace(string, std::regex(R"(\b([a-z])([^ ]+))"), R"($1-$2)");
}

//  ================================================================================================

int main()
{
    assert( match("aaaaa"));
	assert(!match("12345"));
	assert( match("_aaaa"));
	assert( match("_2345"));

//  ------------------------------------------------------

    assert(search("_aa12345______")[0] == "aa12345"     );
    assert(search("_aa12345_6789_")[0] == "aa12345"     );
    assert(search("_aa12345-6789_")[0] == "aa12345-6789");
    assert(search("_aa12345-6789_")[1] ==        "-6789");

    assert(search("___12345-6789_").size() == 0);

//  -------------------------------------------------

    assert(replace("aaaaa 12345") == "a-aaaa 12345");

//  ------------------------------------------------------------------------------------------

    auto data = "123aaaaa456BBBBB789"s; auto begin = std::cbegin(data), end = std::cend(data);

    std::smatch matches;
    
    std::regex pattern(R"([a-z]{4}([a-z]{1}))", std::regex_constants::icase);

    std::cout << "matches = { ";

    for (; std::regex_search(begin, end, matches, pattern); begin = matches.suffix().first)
    {
        std::cout << matches[0] << ' '; // support: boost::tokenizer
    } 

    std::cout << "}\n"; 
    
    begin = std::cbegin(data);

//  ----------------------------------------------------------

    std::sregex_iterator first_1(begin, end, pattern), last_1; 

    std::cout << "matches = { ";

	std::ranges::for_each(first_1, last_1, [](auto && matches){ std::cout << matches[0] << ' '; });

    std::cout << "}\n";

//  ------------------------------------------------------------------------------

    std::sregex_token_iterator first_2(begin, end, pattern, { -1, 0, 1 }), last_2;

    std::cout << "matches = { ";

    std::ranges::for_each(first_2, last_2, [](auto && match){ std::cout << match << ' '; });

    std::cout << "}\n";
}