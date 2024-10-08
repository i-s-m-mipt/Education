#include <complex>
#include <iterator>
#include <string>
#include <string_view>

using namespace std::literals;

#include <boost/spirit/home/x3.hpp>

#include <gtest/gtest.h>

//  ================================================================================================

[[nodiscard]] std::complex < int > parse_complex(std::string_view data)
{
    int value_1{}, value_2{};

    using boost::spirit::x3::_attr;

    const auto set_value_1 = [&value_1](auto && context){ value_1 = _attr(context); };
    const auto set_value_2 = [&value_2](auto && context){ value_2 = _attr(context); };

    using boost::spirit::x3::double_;

    const auto rule = 
    (
        '(' >> double_[set_value_1] >> ',' >> double_[set_value_2] >> ')' |
        '(' >> double_[set_value_1]                                >> ')' |
               double_[set_value_1] >> ',' >> double_[set_value_2]        |
               double_[set_value_1]
    );

    const auto skip = boost::spirit::x3::ascii::space;

    boost::spirit::x3::phrase_parse(std::cbegin(data), std::cend(data), rule, skip);

    return std::complex < int > (value_1, value_2);
}

//  ================================================================================================

TEST(Parser, Complex)
{
    ASSERT_EQ(parse_complex("(1, 2)"sv), std::complex < int > (1, 2));
    ASSERT_EQ(parse_complex("(1   )"sv), std::complex < int > (1, 0));
    ASSERT_EQ(parse_complex(" 1, 2 "sv), std::complex < int > (1, 2));
    ASSERT_EQ(parse_complex(" 1    "sv), std::complex < int > (1, 0));
}

//  ================================================================================================

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}