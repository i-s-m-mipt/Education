#include <algorithm>
#include <cassert>
#include <iterator>
#include <regex>
#include <string>

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////////////////

auto test_v1(const std::string & string)
{
	return std::regex_match(string, std::regex(R"([_[:alpha:]]\w*)")); // support: regex101.com
}

///////////////////////////////////////////////////////////////////////////////////////

auto test_v2(const std::string & string)
{
    std::smatch matches;
    
    std::regex_search(string, matches, std::regex(R"([a-z]{5}\d{5}(-\d{5})?)"));

    return matches;
}

///////////////////////////////////////////////////////////////////////////////////////

auto test_v3(const std::string & string)
{
    return std::regex_replace(string, std::regex(R"(\b([a-z])([^ ]+))"), R"($1-$2)");
}

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        assert(test_v1("aaaaa") == 1);
        
	    assert(test_v1("12345") == 0);

	    assert(test_v1("_aaaa") == 1);

	    assert(test_v1("_2345") == 1);
    }
    
//  -----------------------------------------------------------------------------------

    {
        assert(test_v2("_aaaaa12345_______")[0] == "aaaaa12345");

        assert(test_v2("_aaaaa12345-67890_")[0] == "aaaaa12345-67890");

        assert(test_v2("_aaaaa12345-67890_")[1] == "-67890");
    }

//  -----------------------------------------------------------------------------------

    {
        assert(test_v3("aaaaa 12345") == "a-aaaa 12345");
    }

//  -----------------------------------------------------------------------------------

    {
        auto string = "12345aaaaa67890BBBBB"s;
        
        auto begin = std::cbegin(string);

        std::smatch matches;
        
        std::regex pattern(R"([a-z]{4}([a-z]{1}))", std::regex_constants::icase);

        std::vector < std::string > strings;

        while (std::regex_search(begin, std::cend(string), matches, pattern))
        {
            strings.push_back(matches[0]); // support: boost::tokenizer

            begin = matches.suffix().first;
        }

        assert(strings == std::vector < std::string > ({ "aaaaa", "BBBBB" }));
    }
    
//  -----------------------------------------------------------------------------------

    {
        auto string = "12345aaaaa67890BBBBB"s;
        
        auto begin = std::cbegin(string);

        std::regex pattern(R"([a-z]{4}([a-z]{1}))", std::regex_constants::icase);

        std::vector < std::string > strings;

        std::ranges::for_each
        (
            std::sregex_iterator(begin, std::cend(string), pattern), 

            std::sregex_iterator(), 
            
            [&strings](auto && matches){ strings.push_back(matches[0]); }
        );

        assert(strings == std::vector < std::string > ({ "aaaaa", "BBBBB" }));
    }

//  -----------------------------------------------------------------------------------

    {
        auto string = "12345aaaaa67890BBBBB"s;
        
        auto begin = std::cbegin(string);

        std::regex pattern(R"([a-z]{4}([a-z]{1}))", std::regex_constants::icase);

        std::vector < std::string > strings;

        std::ranges::for_each
        (
            std::sregex_token_iterator(begin, std::cend(string), pattern, { 0, 1 }),
            
            std::sregex_token_iterator(), 
            
            [&strings](auto && match){ strings.push_back(match); }
        );

        assert(strings == std::vector < std::string > ({ "aaaaa", "a", "BBBBB", "B" }));
    }
}