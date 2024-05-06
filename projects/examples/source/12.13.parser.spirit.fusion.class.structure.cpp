#include <exception>
#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>

using namespace std::literals;

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/x3.hpp>

#include <gtest/gtest.h>

//  ================================================================================================

struct Data { char c{}; int i{}; double d{}; }; 

BOOST_FUSION_ADAPT_STRUCT(Data, c, i, d)

//  ================================================================================================

namespace parser
{
    const boost::spirit::x3::rule < class data_tag, Data > data;

    constexpr auto quote = '\'', separator = ',';

    const auto data_def = '{' >> 
    
        boost::spirit::x3::lexeme[ quote  >> 
       (boost::spirit::x3::char_ - quote) >> quote ] >> separator >> 
        boost::spirit::x3::int_                      >> separator >> 
        boost::spirit::x3::double_ >> '}';

    BOOST_SPIRIT_DEFINE(data);

} // namespace parser

//  ================================================================================================

TEST(Parser, Structure)
{
    constexpr auto input = R"({'a',100,1.0})"sv;

    auto begin = std::cbegin(input), end = std::cend(input);

    Data data;

    const auto result = boost::spirit::x3::parse(begin, end, parser::data, data);

    if (!result || begin != end) 
    {
        throw std::invalid_argument("invalid input: " + std::string(input));
    }

    ASSERT_EQ(data.c, 'a'); ASSERT_EQ(data.i, 100); ASSERT_DOUBLE_EQ(data.d, 1.0);
}

//  ================================================================================================

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}