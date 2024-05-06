#include <algorithm>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

using namespace std::literals;

#include <gtest/gtest.h>

//  ================================================================================================

[[nodiscard]] inline bool match_identifier(const std::string & string)
{
	return std::regex_match(string, std::regex(R"([_[:alpha:]]\w*)"));
}

//  ================================================================================================

[[nodiscard]] inline std::smatch search_post_code(const std::string & string)
{
    std::smatch matches;
    
    std::regex_search(string, matches, std::regex(R"(\w{2}\d{5}(-\d{4})?)"));

    return matches;
}

//  ================================================================================================

[[nodiscard]] inline std::string replace_substring(const std::string & string)
{
    return std::regex_replace(string, std::regex(R"(\b(sub)([^ ]+))"), R"(sub-$2)");
}

//  ================================================================================================

TEST(Parser, Regex_Match)
{
    ASSERT_TRUE(match_identifier("hello")         );
	ASSERT_TRUE(match_identifier("12345") == false);
	ASSERT_TRUE(match_identifier("_name")         );
	ASSERT_TRUE(match_identifier("_3.14") == false);
    ASSERT_TRUE(match_identifier("A1234")         );
}

//  ================================================================================================

TEST(Parser, Regex_Search)
{
    ASSERT_EQ(search_post_code("_NY12345______")[0], "NY12345"     );
    ASSERT_EQ(search_post_code("_NY1234506789_")[0], "NY12345"     );
    ASSERT_EQ(search_post_code("_NY12345-6789_")[0], "NY12345-6789");
    ASSERT_EQ(search_post_code("_NY12345-6789_")[1],        "-6789");

    ASSERT_TRUE(std::empty(search_post_code("_$1$2$3$4$_")));
    ASSERT_TRUE(std::empty(search_post_code("NY1234-6789")));
}

//  ================================================================================================

TEST(Parser, Regex_Replace)
{
    ASSERT_EQ(replace_substring("subsequence in the substring"), "sub-sequence in the sub-string");
}

//  ================================================================================================

int main(int argc, char ** argv)
{
    const auto data = "123ABC456DEF789GHI"s; 

    auto begin = std::cbegin(data), end = std::cend(data);

    std::smatch matches;
    
    const std::regex pattern(R"([a-z]{2}([a-z])?)", std::regex_constants::icase);

    for (; std::regex_search(begin, end, matches, pattern); begin = matches.suffix().first)
    {
        std::cout << matches[0] << ' ';
    }

    std::cout << std::endl; begin = std::cbegin(data);

//  ================================================================================================

    {
        const std::sregex_iterator first(begin, end, pattern), last; // note: см. boost::tokenizer

	    std::ranges::for_each(first, last, [](auto && matches){ std::cout << matches[0] << ' '; });

        std::cout << std::endl;
    }

//  ================================================================================================

    {
        const std::sregex_token_iterator first(begin, end, pattern, { -1, 0, 1 }), last;

        std::ranges::for_each(first, last, [](auto && match){ std::cout << match << ' '; });

        std::cout << std::endl;
    }

//  ================================================================================================

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}