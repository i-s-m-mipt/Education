#include <algorithm>
#include <cassert>
#include <iterator>
#include <regex>
#include <string>

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////////////////////

auto test_v1(const std::string & string)
{
	return std::regex_match(string, std::regex(R"([_[:alpha:]]\w*)"));
}

///////////////////////////////////////////////////////////////////////////////////////////

auto test_v2(const std::string & string)
{
    std::smatch matches;
    
    std::regex_search(string, matches, std::regex(R"([a-z]{5}\d{5}(-\d{5})?)"));

    return matches;
}

///////////////////////////////////////////////////////////////////////////////////////////

auto test_v3(const std::string & string)
{
    return std::regex_replace(string, std::regex(R"(\b([a-z])([^ ]+))"), R"($1-$2)");
}

///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto f = false, t = true;

//  ---------------------------------------------------------------------------------------

    assert(test_v1("aaaaa") == t);
	assert(test_v1("12345") == f);
	assert(test_v1("_aaaa") == t);
	assert(test_v1("_2345") == t);

//  ---------------------------------------------------------------------------------------

    assert(test_v2("_aaaaa12345_______")[0] == "aaaaa12345"      );
    assert(test_v2("_aaaaa12345-67890_")[0] == "aaaaa12345-67890");
    assert(test_v2("_aaaaa12345-67890_")[1] ==           "-67890");

    assert(test_v2("______12345-67890_").size() == 0);

//  ---------------------------------------------------------------------------------------

    assert(test_v3("aaaaa 12345") == "a-aaaa 12345");

//  ---------------------------------------------------------------------------------------

    auto data = "12345aaaaa67890BBBBB"s; 
    
    auto begin = std::cbegin(data), end = std::cend(data);

//  ---------------------------------------------------------------------------------------

    std::smatch matches;
    
    std::regex pattern(R"([a-z]{4}([a-z]{1}))", std::regex_constants::icase);

    std::vector < std::string > result;

    for (; std::regex_search(begin, end, matches, pattern); begin = matches.suffix().first)
    {
        result.push_back(matches[0]); // support: boost::tokenizer
    } 

    assert(result == std::vector < std::string > ({ "aaaaa", "BBBBB" })); 

    begin = std::cbegin(data);
    
//  ---------------------------------------------------------------------------------------

    result.clear();

	std::ranges::for_each
    (
        std::sregex_iterator(begin, end, pattern), 

        std::sregex_iterator(), 
        
        [&result](auto && matches){ result.push_back(matches[0]); }
    );

    assert(result == std::vector < std::string > ({ "aaaaa", "BBBBB" })); 

//  ---------------------------------------------------------------------------------------

    result.clear();

    std::ranges::for_each
    (
        std::sregex_token_iterator(begin, end, pattern, { 0, 1 }),
        
        std::sregex_token_iterator(), 
        
        [&result](auto && match){ result.push_back(match); }
    );

    assert(result == std::vector < std::string > ({ "aaaaa", "a", "BBBBB", "B" }));
}