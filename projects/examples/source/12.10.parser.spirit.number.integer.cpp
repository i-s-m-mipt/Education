#include <iterator>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>

using namespace std::literals;

#include <boost/fusion/include/std_tuple.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <boost/spirit/home/x3.hpp>

#include <gtest/gtest.h>

//  ================================================================================================

TEST(Parser, Variable)
{
    const auto data = "1"sv;

    const auto rule = boost::spirit::x3::int_;

    const auto skip = boost::spirit::x3::ascii::space;

    int value{};

    boost::spirit::x3::phrase_parse(std::cbegin(data), std::cend(data), rule, skip, value);

    ASSERT_EQ(value, 1);
}

//  ================================================================================================

TEST(Parser, Pair)
{
    const auto data = "1 2"sv;

    const auto rule = boost::spirit::x3::int_ >> boost::spirit::x3::int_;

    const auto skip = boost::spirit::x3::ascii::space;

    std::pair < int, int > pair;

    boost::spirit::x3::phrase_parse(std::cbegin(data), std::cend(data), rule, skip, pair);

    ASSERT_EQ(pair, std::pair(1, 2));
}

//  ================================================================================================

TEST(Parser, Tuple)
{
    const auto data = "(1, 2)"sv;

    const auto rule = '(' >> boost::spirit::x3::int_ >> ',' >> boost::spirit::x3::int_ >> ')';

    const auto skip = boost::spirit::x3::ascii::space;

    std::tuple < int, int > tuple;

    boost::spirit::x3::phrase_parse(std::cbegin(data), std::cend(data), rule, skip, tuple);

    ASSERT_EQ(tuple, std::tuple(1, 2));
}

//  ================================================================================================

TEST(Parser, Attribute)
{
    const auto data = "1"sv;

    const auto test = [](auto && context)
    { 
        ASSERT_EQ(boost::spirit::x3::_attr(context), 1); 
    };

    const auto rule = boost::spirit::x3::int_[test];

    const auto skip = boost::spirit::x3::ascii::space;

    boost::spirit::x3::phrase_parse(std::cbegin(data), std::cend(data), rule, skip);
}

//  ================================================================================================

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv); 
    
    return RUN_ALL_TESTS();
}