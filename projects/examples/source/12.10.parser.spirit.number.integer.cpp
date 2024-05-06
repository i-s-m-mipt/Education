#include <iostream>
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
    auto value = 0; 
    
    constexpr auto input = "42"sv;

    boost::spirit::x3::parse(std::cbegin(input), std::cend(input), boost::spirit::x3::int_, value);

    ASSERT_EQ(value, 42);
}

//  ================================================================================================

TEST(Parser, Pair)
{
    constexpr auto input = "42 42"sv;

    std::pair < int, int > pair;

    boost::spirit::x3::phrase_parse(std::cbegin(input), std::cend(input), 

        boost::spirit::x3::int_ >> 
        boost::spirit::x3::int_, 
        boost::spirit::x3::space, pair);

    ASSERT_EQ(pair.first , 42);
    ASSERT_EQ(pair.second, 42);
}

//  ================================================================================================

TEST(Parser, Tuple)
{
    constexpr auto input = "(42, 42)"sv;

    std::tuple < int, int > tuple;

    boost::spirit::x3::phrase_parse(std::cbegin(input), std::cend(input), 
    
        '(' >> boost::spirit::x3::int_ >> ',' >> 
               boost::spirit::x3::int_ >> ')', 
               boost::spirit::x3::space, tuple);

    ASSERT_EQ(std::get < 0 > (tuple), 42);
    ASSERT_EQ(std::get < 1 > (tuple), 42);
}

//  ================================================================================================

int main(int argc, char ** argv)
{
    constexpr auto input = "42"sv;

    const auto print = [](auto && context)
    { 
        std::cout << boost::spirit::x3::_attr(context) << std::endl; 
    };

    boost::spirit::x3::parse(std::cbegin(input), std::cend(input), boost::spirit::x3::int_[print]);

//  ================================================================================================

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}